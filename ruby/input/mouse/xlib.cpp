namespace ruby {

struct InputMouseXlib {
  uintptr_t handle = 0;

  Display* display = nullptr;
  Window rootWindow;
  Cursor invisibleCursor;
  unsigned screenWidth = 0;
  unsigned screenHeight = 0;

  struct Mouse {
    bool acquired = false;
    signed numerator = 0;
    signed denominator = 0;
    signed threshold = 0;
    unsigned relativeX = 0;
    unsigned relativeY = 0;
  } ms;

  bool acquire() {
    if(acquired()) return true;

    if(XGrabPointer(display, handle, True, 0, GrabModeAsync, GrabModeAsync, rootWindow, invisibleCursor, CurrentTime) == GrabSuccess) {
      //backup existing cursor acceleration settings
      XGetPointerControl(display, &ms.numerator, &ms.denominator, &ms.threshold);

      //disable cursor acceleration
      XChangePointerControl(display, True, False, 1, 1, 0);

      //center cursor (so that first relative poll returns 0, 0 if mouse has not moved)
      XWarpPointer(display, None, rootWindow, 0, 0, 0, 0, screenWidth / 2, screenHeight / 2);

      return ms.acquired = true;
    } else {
      return ms.acquired = false;
    }
  }

  bool unacquire() {
    if(acquired()) {
      //restore cursor acceleration and release cursor
      XChangePointerControl(display, True, True, ms.numerator, ms.denominator, ms.threshold);
      XUngrabPointer(display, CurrentTime);
      ms.acquired = false;
    }
    return true;
  }

  bool acquired() {
    return ms.acquired;
  }

  bool poll(int16_t* table) {
    Window rootReturn;
    Window childReturn;
    signed rootXReturn = 0;
    signed rootYReturn = 0;
    signed windowXReturn = 0;
    signed windowYReturn = 0;
    unsigned maskReturn = 0;
    XQueryPointer(display, handle, &rootReturn, &childReturn, &rootXReturn, &rootYReturn, &windowXReturn, &windowYReturn, &maskReturn);

    if(acquired()) {
      XWindowAttributes attributes;
      XGetWindowAttributes(display, handle, &attributes);

      //absolute -> relative conversion
      table[mouse(0).axis(0)] = (int16_t)(rootXReturn - screenWidth  / 2);
      table[mouse(0).axis(1)] = (int16_t)(rootYReturn - screenHeight / 2);

      if(table[mouse(0).axis(0)] != 0 || table[mouse(0).axis(1)] != 0) {
        //if mouse moved, re-center mouse for next poll
        XWarpPointer(display, None, rootWindow, 0, 0, 0, 0, screenWidth / 2, screenHeight / 2);
      }
    } else {
      table[mouse(0).axis(0)] = (int16_t)(rootXReturn - ms.relativeX);
      table[mouse(0).axis(1)] = (int16_t)(rootYReturn - ms.relativeY);

      ms.relativeX = rootXReturn;
      ms.relativeY = rootYReturn;
    }

    table[mouse(0).button(0)] = (bool)(maskReturn & Button1Mask);
    table[mouse(0).button(1)] = (bool)(maskReturn & Button2Mask);
    table[mouse(0).button(2)] = (bool)(maskReturn & Button3Mask);
    table[mouse(0).button(3)] = (bool)(maskReturn & Button4Mask);
    table[mouse(0).button(4)] = (bool)(maskReturn & Button5Mask);

    return true;
  }

  bool init(uintptr_t handle) {
    this->handle = handle;
    display = XOpenDisplay(0);
    rootWindow = DefaultRootWindow(display);

    XWindowAttributes attributes;
    XGetWindowAttributes(display, rootWindow, &attributes);
    screenWidth = attributes.width;
    screenHeight = attributes.height;

    //create invisible cursor for use when mouse is acquired
    Pixmap pixmap;
    XColor black, unused;
    static char invisibleData[8] = {0};
    Colormap colormap = DefaultColormap(display, DefaultScreen(display));
    XAllocNamedColor(display, colormap, "black", &black, &unused);
    pixmap = XCreateBitmapFromData(display, handle, invisibleData, 8, 8);
    invisibleCursor = XCreatePixmapCursor(display, pixmap, pixmap, &black, &black, 0, 0);
    XFreePixmap(display, pixmap);
    XFreeColors(display, colormap, &black.pixel, 1, 0);

    ms.acquired = false;
    ms.relativeX = 0;
    ms.relativeY = 0;

    return true;
  }

  void term() {
    unacquire();
    XFreeCursor(display, invisibleCursor);
    XCloseDisplay(display);
  }
};

}