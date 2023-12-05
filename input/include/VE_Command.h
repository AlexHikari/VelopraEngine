#ifndef VE_COMMAND_H
#define VE_COMMAND_H


namespace velopraEngine {
namespace input {
// Command interface
class Command {
public:
  virtual ~Command() {}
  virtual void execute() = 0;
};

} // namespace input
} // namespace velopraEngine

#endif // VE_COMMAND_H
