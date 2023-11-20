#ifndef VE_WINDOW_SIZE_OBSERVER_H
#define VE_WINDOW_SIZE_OBSERVER_H

class IWindowSizeObserver {
public:
	virtual ~IWindowSizeObserver() = default;
	virtual void OnWindowSizeChanged(int width, int height) = 0;
};

#endif //VE_WINDOW_SIZE_OBSERVER_H