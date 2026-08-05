# Reel Forge Driver — Jetson AGX Orin Video Encode/Decode Kernel Module

The Reel Forge Driver is a Linux kernel module that provides direct access to the NVIDIA Jetson AGX Orin's hardware video encode and decode blocks. It supports encoding up to 4 simultaneous 4K60 streams with H.264, H.265, and AV1 codecs, and decoding up to 8 simultaneous 4K60 streams. The driver also interfaces with the Video Image Compositor (VIC) Gen 4.2 for hardware-accelerated image processing including 16-surface blending, lens distortion correction, scaling, deinterlacing, rotation, and temporal noise filtering. A character device interface with ioctls provides encode/decode job management, and a userspace C library wraps the interface for application developers.

## Features

- Hardware
- video
- encode
- (4×4K60,
- H.264/H.265/AV1)

## Quick Start

### Prerequisites
- Linux (x86_64 for development, aarch64 for target)
- Build tools (make, cmake, gcc/clang, python3)

### Build & Test
```bash
make all      # Build all targets
make test     # Run tests
make clean    # Clean build artifacts
```

## Architecture

```
Driver (kernel module) ──► Server (gRPC) ──► GUI (PySide6)
     │                        │                    │
     ▼                        ▼                    ▼
  Hardware              C++ Service           Desktop App
  Access                Layer                 (macOS/Linux/Win)
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| `src/` | Source code |
| `include/` | Public API headers |
| `lib/` | Userspace library |
| `test/` | Unit tests |
| `proto/` | gRPC protocol definitions |
| `packaging/` | Distribution packages |
| `docs/` | Documentation |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** Hardware video decode (8×4K60)
**Audit Score:** 90/100

## 🌐 Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions welcome!

## License

Hardware video decode (8×4K60). See [LICENSE](LICENSE) for details.
