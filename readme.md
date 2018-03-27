# Randar: A Legacy Project
This is the foundation for an old C++ & OpenGL 3D film rendering engine idea. A list of final features is available on the [v1.0.0 tag](https://github.com/alexlitty/randar/releases/tag/v1.0.0).

I've moved onto similar ambitions within the Rust community. The repository is preserved as a learning experience for others and a showcase of some historical work.

## Philosophy
I think this project had a pretty unique structure. The important engine code is in C++ and SWIG was used to wrap the engine in an Node.js "adapter" module, which was further extended with minor features in a "wrapper" module.

The idea was to have the low-level performance of C++ in a language that is easy to prototype with. I found it far more satisfying to write all the unit tests and extended toolage in Node.js instead of C++, for example.

As an added bonus, we could quickly build interfaces by using the Node.js module in Electron apps!

## License
See the `LICENSE` file.
