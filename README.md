Getan - a modern text editor
============================

Project state: **HEAVY DEVELOPMENT** (core architecture is *-almost-* done)

1. What is this?
----------------
Getan is a modern text editor for programmers. With the main goals of being
fast, lightweight and highly customizable, this text editor was made to appeal
both new and old programmers around the world. The main inspiration is the
superb ViM text editor, but I took some inspirations from other text editors
like Sublime Text Editor and (even) Emacs.

    getan (/ɡəˈtaːn/) - ppart. tun.
    tun (/tuːn/) - tut, tat, hat getan
        I v/t
          1. to do;
          2. eine Äußerung tun: make a remark;
          ...
          (http://www.wordreference.com/deen/tun)

So, *getan* is (almost) German for *done*; to get something done. ;-)

2. Why?
-------
You may ask yourself: why creating **another** text editor? See, NONE of them
completely satisfy me as a programmer. The one that I use regularly is *Vim*;
but *Vim* is only a layer upon *Vi*, that is a layer upon *Ex*. It's too much
abstractions, creating a kind of slow environment. Start using more plugins (at
least 5) and you will know what I'm talking about. Besides, I think *VimScript*
is slow and a bit counter intuitive. In other hand, Vim has a lot of power tools
to make coding a lot fast!<br />
*Emacs* does not need more plugins to be slow (at least in the startup): it's
slow from the very beginning. But, the same way as *Vim*, it has a lot of tools
to make coding something fun. The *LaTeX* integration is great and I don't know
better software kit to develop **LISP** than *SLIME*.<br />
*Sublime Text* is fine; it has only one problem: it's **NOT FOSS (Free Open
Source Software)!**<br />
There's *Atom*, from GitHub group. But there's at least 2 peculiarities with it:
it aims on *web developers* and depends on **Node.js**. That's not bad at all,
but I don't need **Node.js** support if I write most of my code in **C**!<br />
I think I can't even talk about *NetBeans* or *Eclipse*. They have a polluted UI
and don't even think on running them on an older PC.<br />
Who uses *Anjuta* nowadays? I don't know. It has an interesting interface... But
there isn't any "terminal" mode!<br />
So, for a more comfortable development environment, lightweight and fast, to
really get things DONE, I'm creating my own text editor.

3. Project Goals
----------------
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

4. Dependencies
---------------
For now, these are the project dependencies:
  - ncurses;
  - wxWidgets (for the graphical interface) [future];
  - Lua 5.2 and liblua5.2-dev (to run plugins) [future].

5. A bit about coding style
---------------------------
This is a small project and (at this time) has only one developer: **me**. But
I hope that someday there will be a lot more developers and enthusiastics. So
let's talk a little bit about coding standards.
In fact, I just make use of the Kernel coding style as presented here:
<https://www.kernel.org/doc/Documentation/CodingStyle>

I have only added one thing to the standard. Instead of declaring:

    if (conditional) {
        ...
    }

I prefer to declare this way:

    if ( conditional ) {
        ...
    }

Note the spaces inside the parenthesis. At least for me, it makes more clear the
conditionals inside the parenthesis. So, if I have more than one conditional in
the 'if' statement, I can easily see all of them and where they finish:

    if ( (conditional1) || (conditional2) ) {
        ...
    }

This rule applies also to *switch-case*, *while* and *for* statements.

Oh! And, by the way, DON'T YOU EVER, EVER use TABs! As a friend of mine used to
say, TABs are evil! Indenting is done with 4 SPACEs! The Kernel coding style
establishes TABs 8 characters long to indent code. I'm Ok with that, but if
you try to keep your code aligned in the maximum of 80 characters, the 80th
column can change depending on your indenting level. One thing that is said
in the Kernel coding style applies here also: if you need more than 3 indenting
levels, you should really consider refactoring your code.

That's it! Now you are able to contribute to my project. ;-)

6. High-level code organization
-------------------------------

      +-----------+    +-----------+
      | Graphical |    |  Terminal |
      | Interface |    | Interface |
      +-----------+    +-----------+
            |                |
            +----------------+
                |        |
                |        V
                |   +----------+
                |   |  Plugin  |
                |   |   Core   |
                |   +----------+
                |        |
                V        V
    +-------------------------------+
    |        Getan API Core         |
    |  +------------+------------+  |
    |  |   Editor   |  Shortcut  |  |
    |  |  Commands  |  Wrapper   |  |
    |  +------------+------------+  |
    |  |   Buffers  |    Files   |  |
    |  |            |            |  |
    |  +------------+------------+  |
    +-------------------------------+

