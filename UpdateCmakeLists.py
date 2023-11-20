"""
CMakeLists Updater Script

This script automatically updates the CMakeLists.txt files in a given set of modules.
It scans for .cpp (source) and .h (header) files in each module's directory and updates the
corresponding set() directives in the CMakeLists.txt files. The script also prints out
which files have been added or removed, with color coding for clarity (green for added,
red for removed). If no changes are detected, it indicates that the module is already up to date.
"""

import os
import re

# ANSI escape sequences for colors
class Colors:
    ADDED = '\033[92m'  # GREEN
    REMOVED = '\033[91m' # RED
    RESET = '\033[0m'   # RESET COLOR

def find_files(directory, extensions):
    files_list = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(extensions):
                relative_path = os.path.relpath(os.path.join(root, file), directory)
                files_list.append(relative_path.replace('\\', '/'))
    return files_list

def parse_existing_files(lines, module_name):
    existing_files = {'source': [], 'header': []}
    capture = False
    for line in lines:
        if f'set({module_name}_SOURCE_FILES' in line:
            capture = 'source'
        elif f'set({module_name}_HEADER_FILES' in line:
            capture = 'header'
        elif line.strip() == ')' and capture:
            capture = False
        elif capture:
            existing_files[capture].append(line.strip())

    return existing_files

def update_cmake_lists(cmake_path, module_name, new_source_files, new_header_files):
    with open(cmake_path, 'r') as file:
        lines = file.readlines()

    existing_files = parse_existing_files(lines, module_name)

    # Check if set directives exist, if not, add them
    source_set_exists = any(f'set({module_name}_SOURCE_FILES' in line for line in lines)
    header_set_exists = any(f'set({module_name}_HEADER_FILES' in line for line in lines)

    removed_source_files = set(existing_files['source']) - set(new_source_files)
    added_source_files = set(new_source_files) - set(existing_files['source'])
    removed_header_files = set(existing_files['header']) - set(new_header_files)
    added_header_files = set(new_header_files) - set(existing_files['header'])

    new_lines = []
    skip = False
    for line in lines:
        if f'set({module_name}_SOURCE_FILES' in line or f'set({module_name}_HEADER_FILES' in line:
            skip = True
            new_lines.append(line)
            if f'set({module_name}_SOURCE_FILES' in line:
                new_lines.extend(['    ' + file + '\n' for file in new_source_files])
                new_lines.append(')\n')
            elif f'set({module_name}_HEADER_FILES' in line:
                new_lines.extend(['    ' + file + '\n' for file in new_header_files])
                new_lines.append(')\n')
        elif skip and line.strip() == ')':
            skip = False
            continue
        elif not skip:
            new_lines.append(line)

    # Add set directives if they don't exist and there are files to add
    if not source_set_exists and new_source_files:
        new_lines.append(f'set({module_name}_SOURCE_FILES\n')
        new_lines.extend(['    ' + file + '\n' for file in new_source_files])
        new_lines.append(')\n')

    if not header_set_exists and new_header_files:
        new_lines.append(f'set({module_name}_HEADER_FILES\n')
        new_lines.extend(['    ' + file + '\n' for file in new_header_files])
        new_lines.append(')\n')

    with open(cmake_path, 'w') as file:
        file.writelines(new_lines)

    return added_source_files, removed_source_files, added_header_files, removed_header_files



def print_changes(module, added, removed, file_type):
    if added or removed:
        if added:
            print(f"{Colors.ADDED}Added {file_type} in {module}:{Colors.RESET} {', '.join(added)}")
        if removed:
            print(f"{Colors.REMOVED}Removed {file_type} in {module}:{Colors.RESET} {', '.join(removed)}")
    else:
        print(f"{module} {file_type} are already up to date.")

def main():
    modules = {
        'core': './core',
        'input': './input',
        'rendering': './rendering',
        'ui': './ui'
    }

    for module, path in modules.items():
        module_name = module.upper()
        new_source_files = find_files(path, '.cpp')
        new_header_files = find_files(path, '.h')
        cmake_path = os.path.join(path, 'CMakeLists.txt')

        added_source, removed_source, added_header, removed_header = update_cmake_lists(cmake_path, module_name, new_source_files, new_header_files)

        print_changes(module, added_source, removed_source, 'sources')
        print_changes(module, added_header, removed_header, 'headers')

if __name__ == "__main__":
    main()
