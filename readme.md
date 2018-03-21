# Randar: A Legacy Project
This is the foundation for an old C++ & OpenGL 3D film rendering engine intended for my own animated productions.

The repository is preserved as a learning experience for others and a showcase of some old historical work I'm proud of.

# Postmortem
The initial intent was to make a rendering library I enjoyed using and could deeply configure for oddball graphics work. Other C++ alternatives felt too limiting: They often abstracted too much away in an inconfigurable manner, featured an old C style API that was difficult to wrap modern work around, and were severely lacking in documentation. The professional alternatives were definitely an option but simply too expensive for my desired budget.

Since the library would serve as the heart of the animation studio, I also found it important to keep it open-source or developed in-house to ensure complete control over the software and keep expenses low. The decision seemed clear at the time, leading me to start a deep focus on the library and graphics engineering in general.

I eventually learned of similar rendering library efforts that started earlier in the Rust community. While my idea slowly came to some form of stability it wasn't nearly as feature-complete as the more recent developments; I was mostly pursuing Randar development alone and couldn't compete.

I've decided to retire this project as a result but the dream of my creating my own animated stories lives on.

All that aside, the most important lessons I learned:

## Too big
I didn't realize it at the time but my project started to become the very thing I despised: A big conglomerate library of "things" that had some tangible relationship with one another. I think I did a relatively good job keeping it cleaned and organized (as we all do) but the scope still grew out of control.

## Not the right technology
Rust is amazing and I wish I stumbled upon it sooner. For the studio's purposes, it's an amazing long-term replacement for C++. If you're my friend you know I won't stop talking about it -- I really think it's silly to make anything in C and C++ today when you have the time and ability to use Rust.

Every aspect we need in _modern_ programming is built into Rust and Cargo; I'm most fond of the easy testability, the improved modularity, and the guaranteed memory safety. It's totally the future.

## Working alone
Looking at the Rust community there's a clear and irrefutable power in numbers. As fun as it was, I'm extremely critical of pursuing such a big project on my own again.

# Installation
You're welcome to give the library a try locally if it works for you. To install, simply run:

    git clone https://github.com/alexlitty/randar.git
    cd randar
    ./run/install

Randar was created to be Debian-only. Ubuntu, Linux Mint, and other Debian derivatives may work out-of-the-box. If dependencies are installed manually, Randar should work on most major Linux distributions.

# License
See the `LICENSE` file.
