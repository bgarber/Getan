Getan - a modern text editor for old school programmers
=======================================================

1. What is this?
Getan is a modern text editor for programmers. With the main goals of being
fast, lightweight and highly customizable, this text editor was made to appeal
both new and old programmers around the world. The main inpiration is the superb
ViM text editor, but we took some inspirations from other text editors like
Sublime Text Editor and (even) Emacs.

    getan (/ɡəˈtaːn/) - ppart tun.
    tun (/tuːn/) - tut, tat, hat getan
        I v/t
          1. to do;
          2. eine Äußerung tun: make a remark;
          ...
          (http://www.wordreference.com/deen/tun)

So, *getan* is (almost) German for *done*, get something done. ;-)

2. Project Requirements:
These are things we NEED to keep in mind every time we develop a new feature on
Getan:
  - Lightweight and fast (run even on older PC's);
  - Highly customization (we can be fancy too!);
  - Run both in terminal mode or with a GUI;
  - Support true colors (24 bits) even on terminal;
  - Be portable (run on Windows, Linux or MacOS X);
  - Carefully organized keyboard shortcuts;
  - Better organized CODE;
  - Easy to hack on to.

3. Project organization:

  +-----------+   +-----------+
  | Graphical |   |  Terminal |
  | Interface |   | Interface |
  +-----------+   +-----------+
        |               |
        +---------------+
                |
                v
  +---------+-----------------+
  |         |   |  Shortcut   |
  |         |   |  Wrapper    |
  |         |   +-------------+
  |         |      Editor     |
  |         |     Commands    |
  |         +-----------------+    +-------------+
  |                           |    |             |
  |     Buffers Manager       |<-->| Plugin Core |
  |                           |    |             |
  +---------------------------+    +-------------+
  |      Files Manager        |
  +---------------------------+
