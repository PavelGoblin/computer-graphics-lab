# Experiment 01: A Brief Study of Various Types of Input and Output Devices

_This is a theory-only experiment. No programming required._

---

## 1. Input Devices

Input devices are hardware components that allow users to enter data, instructions, or commands into a computer system.

### 1.1 Keyboard
- **Description**: Most common input device with alphanumeric keys
- **Types**: QWERTY, AZERTY, DVORAK, virtual/on-screen keyboards
- **Working**: Pressing a key closes a circuit, generating a scan code sent to the CPU
- **Interfaces**: USB, PS/2, Bluetooth (wireless)

### 1.2 Mouse
- **Description**: Pointing device that detects 2D motion relative to a surface
- **Types**:
  - **Mechanical**: Rubber ball with rollers (obsolete)
  - **Optical**: LED + photodiode detects surface movement
  - **Laser**: More precise than optical
  - **Wireless**: RF/Bluetooth, no cable
- **Working**: Movement sensed → cursor position updated on screen
- **Buttons**: Left (select), Right (context menu), Scroll wheel (scroll/zoom)

### 1.3 Touchscreen
- **Description**: Display that detects touch input directly on screen
- **Types**:
  - **Resistive**: Pressure-sensitive, works with any object (cheaper, lower clarity)
  - **Capacitive**: Electrical conductivity of finger (multi-touch, higher clarity)
  - **Infrared**: IR beams interrupted by touch
- **Applications**: Smartphones, tablets, ATMs, kiosks

### 1.4 Scanner
- **Description**: Converts physical documents/photos into digital images
- **Types**:
  - **Flatbed**: Document placed on glass, scan head moves
  - **Sheet-fed**: Paper pulled through rollers
  - **Drum**: High-resolution, rotates document past sensor
  - **Handheld**: Manual scanning
- **Resolution unit**: DPI (Dots Per Inch)

### 1.5 Digitizer / Graphics Tablet
- **Description**: Converts analog hand-drawn input to digital coordinates
- **Working**: Pen (stylus) on pressure-sensitive surface
- **Uses**: CAD (Computer-Aided Design), digital art, animation
- **Parameters**: Pressure sensitivity levels, resolution (LPI)

### 1.6 Light Pen
- **Description**: Pen-like device with light sensor at tip
- **Working**: Detects light from CRT screen phosphor when pointed
- **Limitation**: Only works with CRT monitors (largely obsolete)

### 1.7 Joystick
- **Description**: Lever that pivots on a base, reporting angle/direction
- **Types**: Analog, digital, force-feedback
- **Uses**: Gaming, flight simulators, industrial controls

### 1.8 Trackball
- **Description**: Stationary base with a ball on top, moved by fingers
- **Advantage**: No arm movement needed (ergonomic)
- **Uses**: CAD workstations, kiosks, accessibility

### 1.9 Microphone
- **Description**: Converts sound waves into electrical signals
- **Types**: Dynamic, condenser, ribbon
- **Uses**: Voice recording, speech recognition, VoIP

### 1.10 Camera / Webcam
- **Description**: Captures images/video as digital data
- **Components**: Lens, image sensor (CCD/CMOS), ADC
- **Resolution**: Measured in megapixels (MP)

### 1.11 Barcode Reader
- **Description**: Scans barcodes (parallel lines/2D patterns)
- **Types**: Laser, CCD (image-based), camera-based
- **Common standards**: UPC, Code 128, QR Code

### 1.12 Biometric Scanner
- **Description**: Captures biological characteristics for identification
- **Types**: Fingerprint, iris/retina, face recognition, voice recognition

### 1.13 Other Input Devices
| Device | Purpose |
|--------|---------|
| Magnetic Stripe Reader | Reads data from magnetic stripe on cards |
| RFID Reader | Reads radio frequency identification tags |
| Touchpad | Built-in pointing device on laptops |
| Gamepad | Handheld controller with buttons/thumbsticks |
| Data Glove | Captures hand/finger movement for VR |

---

## 2. Output Devices

Output devices convert processed digital data into human-readable form.

### 2.1 Monitor (Display)
#### CRT (Cathode Ray Tube)
- **Working**: Electron beam fires at phosphor-coated screen
- **Scanning**: Raster scan (left-to-right, top-to-bottom) or vector scan
- **Resolution**: Determined by beam precision
- **Color**: RGB phosphor dots + shadow mask
- **Limitations**: Bulky, high power consumption — largely obsolete

#### LCD (Liquid Crystal Display)
- **Working**: Liquid crystals twisted by electric field to block/pass backlight
- **Types**:
  - **TN (Twisted Nematic)**: Fast response, cheap, poor viewing angles
  - **IPS (In-Plane Switching)**: Better color/angles, more expensive
  - **VA (Vertical Alignment)**: Better contrast than TN
- **Backlight**: LED (modern CCFL older)

#### LED Display
- **Working**: Array of LEDs directly form the image (no backlight needed)
- **Types**: OLED (Organic LED), MicroLED
- **Advantages**: True blacks, infinite contrast, flexible screens

#### Related Concepts
- **Resolution**: Number of pixels (e.g., 1920×1080, 3840×2160)
- **Refresh Rate**: Hz (60Hz, 120Hz, 144Hz)
- **Aspect Ratio**: 16:9, 4:3, 21:9
- **Color Depth**: Bits per pixel (24-bit = 16.7M colors)

### 2.2 Printer
#### Impact Printers (Strike on ribbon → paper)
- **Dot Matrix**: Pins strike ribbon; cheap, noisy, multi-part forms
- **Daisy Wheel**: Letter-quality, slow, obsolete

#### Non-Impact Printers
- **Inkjet**: Sprays tiny ink droplets; good quality, slow, expensive ink
- **Laser**: Toner + electrostatic drum; fast, high-quality, cost-effective for volume
- **Thermal**: Heated pins on thermal paper; used in receipts, labels
- **3D Printer**: Deposits material layer-by-layer to create 3D objects

#### Printer Specifications
| Parameter | Description |
|-----------|-------------|
| **DPI** | Dots per inch — resolution |
| **PPM** | Pages per minute — speed |
| **Duty Cycle** | Monthly page capacity |
| **Connectivity** | USB, Ethernet, Wi-Fi |

### 2.3 Plotter
- **Description**: Vector-based output for large-format drawings
- **Types**: Drum (rolling paper), Flatbed (stationary paper)
- **Uses**: Engineering blueprints, architectural drawings, CAD output
- **Difference from printer**: Uses pen to draw continuous lines (not dots)

### 2.4 Projector
- **Description**: Projects computer output onto a large screen
- **Types**:
  - **DLP (Digital Light Processing)**: Micromirror array (DMD chip)
  - **LCD Projector**: Three LCD panels (R, G, B)
  - **LCoS (Liquid Crystal on Silicon)**: Hybrid of DLP and LCD
- **Specifications**: Lumens (brightness), contrast ratio, resolution

### 2.5 Speakers / Headphones
- **Description**: Converts electrical audio signals into sound waves
- **Types**: Stereo, surround sound (5.1, 7.1), studio monitors
- **Specifications**: Frequency response, impedance, wattage

### 2.6 VR / AR Headsets
- **VR (Virtual Reality)**: Fully immersive digital environment
  - Examples: Oculus Rift, HTC Vive, PlayStation VR
- **AR (Augmented Reality)**: Digital overlay on real world
  - Examples: Microsoft HoloLens, Magic Leap

---

## 3. Classification Summary

### By Data Flow
```
                    ┌─────────────────┐
Input Devices ─────▶│  Computer / CPU │─────▶ Output Devices
                    └─────────────────┘
```

### By Data Type
| Data Type | Input Devices | Output Devices |
|-----------|---------------|----------------|
| Text/Numbers | Keyboard, Barcode reader | Monitor, Printer |
| Graphics/Images | Scanner, Camera, Digitizer | Monitor, Plotter |
| Audio | Microphone | Speaker, Headphones |
| Video | Camera, Webcam | Monitor, Projector |
| Position/Motion | Mouse, Joystick, Touchscreen | — |
| Biometric | Fingerprint scanner, Iris scanner | — |

### Hardcopy vs Softcopy
| Aspect | Hardcopy Output | Softcopy Output |
|--------|-----------------|-----------------|
| Medium | Physical (paper, film) | Electronic (screen) |
| Permanent | Yes | No (volatile) |
| Portable | Carried physically | Transmitted digitally |
| Devices | Printer, Plotter | Monitor, Projector |

---

## 4. Sample Questions

1. Differentiate between impact and non-impact printers with examples.
2. Compare CRT, LCD, and LED display technologies.
3. What is the difference between a scanner and a digitizer?
4. Explain the working of a laser printer with a diagram.
5. Classify input devices based on the type of data they handle.
6. What are the advantages of capacitive touchscreens over resistive?
7. Define DPI, PPM, and refresh rate.
8. What is the difference between hardcopy and softcopy output?
