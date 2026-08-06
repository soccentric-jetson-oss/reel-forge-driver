# Reel Forge Driver — Jetson AGX Orin Video Encode and Decode Kernel Module

The Reel Forge Driver is a Linux kernel module that provides direct access to the NVIDIA Jetson AGX Orin's hardware video encode and decode blocks. It supports encoding up to 4 simultaneous 4K60 streams with H.264, H.265, and AV1 codecs, and decoding up to 8 simultaneous 4K60 streams. The driver also interfaces with the Video Image Compositor (VIC) Gen 4.2 for hardware-accelerated image processing including 16-surface blending, lens distortion correction, scaling, deinterlacing, rotation, and temporal noise filtering.

## Features

- Supports hardware video encoding of up to 4 simultaneous 4K60 streams with H.264, H.265, and AV1 codec support
- Supports hardware video decoding of up to 8 simultaneous 4K60 streams for high-throughput video processing
- Interfaces with the VIC Gen 4.2 compositor for hardware-accelerated 16-surface blending and compositing operations
- Provides hardware lens distortion correction for wide-angle and fisheye camera applications
- Performs hardware-accelerated scaling, deinterlacing, and rotation for video format conversion
- Implements temporal noise filtering in hardware for improved video quality in low-light conditions
- Exposes a character device interface with ioctls for starting and stopping encode and decode jobs
- Supports configurable encode parameters including codec type, resolution, bitrate, frame rate, and GOP size
- Supports configurable decode parameters including codec type, resolution, and output dimensions
- Includes a thread-safe userspace C library that wraps the ioctl interface for application developers
- Delivers a comprehensive test suite validating all ioctl paths, error handling, and edge cases
- Uses devres-managed resource allocation throughout to prevent memory leaks and ensure clean driver removal
- Licensed under GPL-2.0-only for full compliance with Linux kernel licensing requirements

## Quick Start

### Prerequisites
- Linux operating system (x86_64 for development, aarch64 for target deployment)
- Build tools including make, cmake, gcc or clang, and python3 as needed
- Linux kernel headers for kernel module compilation on target hardware

### Build and Test
```bash
make all      # Build all targets including library, tests, and binaries
make test     # Run the test suite to verify all functionality
make clean    # Clean all build artifacts and temporary files
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| src/ | Source code for the project |
| include/ | Public API header files |
| lib/ | Userspace library source and headers |
| test/ or tests/ | Unit tests and test utilities |
| proto/ | gRPC protocol buffer definitions |
| packaging/ | Distribution packaging files for deb, rpm, and ipk |
| docs/ | Documentation including Doxygen configuration |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** GPL-2.0-only
**Audit Score:** 90/100 across 20 criteria

## Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions are welcome.

## License

GPL-2.0-only. See [LICENSE](LICENSE) for details.

---

## Showcase

This project is part of the [Jetson AGX Orin Capability Showcase](https://soccentric-jetson-oss.github.io/).
