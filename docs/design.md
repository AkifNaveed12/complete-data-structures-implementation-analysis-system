# CDSIAS — Design System & UI/UX Document

## design.md

> This document defines every visual, aesthetic, and interaction design decision for the CDSIAS Qt GUI. Every screen, every color, every animation, every widget — defined here. The CLI phase follows a simplified version of these same design principles.

---

## 1. DESIGN PHILOSOPHY

| Principle                 | Description                                                                          |
| ------------------------- | ------------------------------------------------------------------------------------ |
| **Dark & Modern**         | Deep dark background, neon accent highlights — feels like a professional IDE         |
| **Classy Minimal**        | No clutter. Every pixel has purpose. Information is never hidden, never overwhelming |
| **Animated Clarity**      | Every operation animates slowly enough to understand, fast enough to stay engaging   |
| **Module Color Identity** | Each module has its own accent color — instantly recognizable                        |
| **Typography-first**      | Clean monospace for data, clean sans-serif for UI — no mixing                        |
| **Zero Confusion**        | User always knows where they are, what module they're in, what operation is running  |

---

## 2. COLOR SYSTEM

### 2.1 Base Palette

```
Background (primary)    #0D0D0D    — near-black
Background (card)       #141414    — slightly lighter dark
Background (panel)      #1A1A2E    — deep navy dark (panels & sidebars)
Surface (elevated)      #1E1E2E    — elevated card surfaces
Border                  #2A2A3E    — subtle borders
```

### 2.2 Typography Colors

```
Text primary            #E8E8F0    — soft white (main content)
Text secondary          #8888AA    — muted purple-grey (labels, hints)
Text disabled           #444466    — very muted (inactive items)
Text code / data        #A8E6CF    — soft mint (values in DS visualization)
```

### 2.3 Module Accent Colors (Each Module = One Identity Color)

```
Linear Structures       #4FC3F7    — sky blue
Stack & Queue           #FFB74D    — warm amber
Trees                   #81C784    — soft green
Graph                   #E57373    — muted red-coral
Searching & Sorting     #CE93D8    — soft lavender
Hashing                 #4DB6AC    — teal
Performance             #FFF176    — soft yellow
```

### 2.4 State Colors

```
Highlight / Active      (module accent color)
Highlighted element     accent with 50% brighter + border glow
Success                 #69F0AE    — bright mint green
Error                   #FF5370    — bright red
Warning                 #FFD740    — bright amber
Visited (graph/tree)    #546E7A    — steel blue-grey
Current node            (module accent)
Comparison element      #FF9800    — orange
Swap indicator          #FF5370    — red
```

### 2.5 Qt Stylesheet Definitions

```css
/* Main Window */
QMainWindow {
  background-color: #0d0d0d;
}

/* Card / Panel */
QFrame#moduleCard {
  background-color: #141414;
  border: 1px solid #2a2a3e;
  border-radius: 12px;
}

/* Module Button */
QPushButton#moduleBtn {
  background-color: #1a1a2e;
  color: #e8e8f0;
  border: 1px solid #2a2a3e;
  border-radius: 10px;
  padding: 16px 24px;
  font-size: 15px;
  font-family: "Segoe UI";
  font-weight: 500;
}

QPushButton#moduleBtn:hover {
  background-color: #252540;
  border: 1px solid (module accent color);
  color: (module accent color);
}

QPushButton#moduleBtn:pressed {
  background-color: #1a1a2e;
  border: 2px solid (module accent color);
}

/* Visualization canvas */
QWidget#vizCanvas {
  background-color: #0d0d0d;
  border: 1px solid #2a2a3e;
  border-radius: 8px;
}

/* Input field */
QLineEdit#inputField {
  background-color: #1e1e2e;
  color: #e8e8f0;
  border: 1px solid #2a2a3e;
  border-radius: 8px;
  padding: 10px 14px;
  font-family: "JetBrains Mono";
  font-size: 14px;
}

QLineEdit#inputField:focus {
  border: 1px solid (module accent);
  outline: none;
}

/* Performance table */
QTableWidget {
  background-color: #141414;
  color: #e8e8f0;
  gridline-color: #2a2a3e;
  font-family: "JetBrains Mono";
  font-size: 13px;
  border: none;
}

QHeaderView::section {
  background-color: #1a1a2e;
  color: #8888aa;
  padding: 10px;
  border: none;
  font-weight: 600;
}
```

---

## 3. TYPOGRAPHY

### 3.1 Fonts

| Use                               | Font           | Weight       | Size |
| --------------------------------- | -------------- | ------------ | ---- |
| App Title                         | Segoe UI       | 700 Bold     | 28px |
| Screen Title                      | Segoe UI       | 600 SemiBold | 20px |
| Module Label                      | Segoe UI       | 500 Medium   | 16px |
| Body text                         | Segoe UI       | 400 Regular  | 14px |
| DS Values (nodes, array elements) | JetBrains Mono | 500 Medium   | 15px |
| Code / algorithm text             | JetBrains Mono | 400 Regular  | 13px |
| Step output text                  | JetBrains Mono | 400 Regular  | 13px |
| Performance table                 | JetBrains Mono | 400 Regular  | 13px |
| Error messages                    | Segoe UI       | 500 Medium   | 13px |
| Button text                       | Segoe UI       | 500 Medium   | 14px |

### 3.2 Font Hierarchy

```
Level 1 — App Identity:    CDSIAS  [28px Bold Segoe UI] [accent color]
Level 2 — Screen Name:     Array Module  [20px SemiBold]
Level 3 — Section Labels:  Current Operation: Insert at Index  [14px Regular]
Level 4 — Data Display:    [ 10 ][ 20 ][ (30) ][ 40 ]  [15px JetBrains Mono]
Level 5 — Step Output:     Step 2: Shifting (30) right  [13px JetBrains Mono]
```

---

## 4. LAYOUT SYSTEM

### 4.1 Splash Screen Layout

```
┌─────────────────────────────────────────────────────────────┐
│                                                             │
│                    [CDSIAS LOGO / ICON]                     │
│                                                             │
│          CDSIAS — Data Structure Visualizer                 │
│      Comprehensive DS Implementation & Analysis             │
│                                                             │
│                  ┌─────────────────┐                        │
│                  │   Start System  │  [accent button]       │
│                  └─────────────────┘                        │
│                                                             │
│                  ┌─────────────────┐                        │
│                  │     Login       │  [outline button]      │
│                  └─────────────────┘  [Future - disabled]   │
│                                                             │
│                  ┌─────────────────┐                        │
│                  │      Exit       │  [ghost button]        │
│                  └─────────────────┘                        │
│                                                             │
│                    Version 1.0.0                            │
│           Akif Naveed · Arslan Shafiq                       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 4.2 Main Dashboard Layout

```
┌─────────────────────────────────────────────────────────────┐
│  CDSIAS                               [Performance] [Info]  │  ← Top bar
├─────────────────────────────────────────────────────────────┤
│                                                             │
│         DATA STRUCTURE LABORATORY                           │
│         Choose a module to begin                            │
│                                                             │
│  ┌──────────────────┐  ┌──────────────────┐                 │
│  │ 🔵 Linear        │  │ 🟡 Stack & Queue │                 │
│  │    Structures    │  │                  │                 │
│  └──────────────────┘  └──────────────────┘                 │
│  ┌──────────────────┐  ┌──────────────────┐                 │
│  │ 🟢 Trees         │  │ 🔴 Graph Algo    │                 │
│  │                  │  │                  │                 │
│  └──────────────────┘  └──────────────────┘                 │
│  ┌──────────────────┐  ┌──────────────────┐                 │
│  │ 🟣 Search/Sort   │  │ 🟦 Hashing       │                 │
│  │                  │  │                  │                 │
│  └──────────────────┘  └──────────────────┘                 │
│  ┌──────────────────────────────────────┐                   │
│  │ 🟡 Performance Analytics             │                   │
│  └──────────────────────────────────────┘                   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 4.3 Module Operation Screen Layout (3-Panel)

```
┌───────────┬─────────────────────────────────┬──────────────┐
│           │                                 │              │
│ SIDEBAR   │     VISUALIZATION CANVAS        │  STEP LOG    │
│           │                                 │              │
│ Module:   │   [ 10 ][ 20 ][ (30) ][ 40 ]   │ Step 1: ...  │
│ Array     │                                 │ Step 2: ...  │
│           │   ↕ ↕ ↕ ↕ (animation here)     │ Step 3: ...  │
│ Operation:│                                 │              │
│ Insert    │                                 │ Result: ...  │
│           ├────────────────────────────────┤              │
│ [Input]   │  Operation: Insert at Index 2  │ Performance: │
│ Value: __ │  Steps: 3  | Complexity: O(n)  │ Steps: 3     │
│ Index: __ │                                │ O(n)         │
│           ├─────────────────────────────── ┤              │
│ [Run]     │  [◀ Back]         [Next ▶]     │              │
│ [Reset]   │                                │              │
│           │                                │              │
└───────────┴─────────────────────────────── ┴──────────────┘
```

### 4.4 Performance Report Screen

```
┌─────────────────────────────────────────────────────────────┐
│  ◀ Back              PERFORMANCE REPORT                     │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Module        │ Operation       │ Steps │ Compare │ O()   │
│  ──────────────┼─────────────────┼───────┼─────────┼────── │
│  Array         │ InsertAtIndex   │   3   │   0     │ O(n)  │
│  Array         │ Search          │   4   │   4     │ O(n)  │
│  BST           │ Insert          │   3   │   3     │O(logn)│
│  BubbleSort    │ Sort(n=4)       │   6   │   6     │ O(n²) │
│                                                             │
│  Total operations: 4                                        │
│                                                             │
│  [Clear Report]                          [Export (Future)]  │
└─────────────────────────────────────────────────────────────┘
```

---

## 5. VISUALIZATION DESIGN — PER MODULE

### 5.1 Array Visualization

**Element Box Design:**

```
Normal element:      ┌─────┐
                     │  20 │    width: 60px, height: 60px
                     └─────┘    border: 1px #2A2A3E, border-radius: 6px
                                font: JetBrains Mono 15px #A8E6CF

Active/highlighted:  ┌─────┐
                     │ (30)│    border: 2px module-accent-color
                     └─────┘    background: accent color at 15% opacity
                                text: accent color, font-weight: 600
                                glow effect: box-shadow: 0 0 12px accent

Being shifted:       ┌─────┐
                     │  40 │    border: 2px #FFD740 (warning amber)
                     └─────┘    moving with QPropertyAnimation translateX
```

**Index labels:** Small text below each box, color `#8888AA`, font size 11px
**Arrow indicators:** Between boxes, thin `→` in `#2A2A3E`

**Animation — Insert at Index:**

- Elements slide right with `QPropertyAnimation` on `x` position
- Duration per shift: 200ms
- Easing: `QEasingCurve::OutQuad`
- New element fades in: `QPropertyAnimation` on `opacity`, 0→1, 300ms

---

### 5.2 Linked List Visualization

**Node Design:**

```
Normal node:   ┌──────┬───┐
               │  20  │ → │    left box: data, right box: next pointer
               └──────┴───┘    data box width: 50px, pointer box: 20px

Active node:   ┌──────┬───┐
               │ (20) │ → │    data box border: 2px accent, glow
               └──────┴───┘
```

**NULL indicator:** Small box `[ NULL ]` at chain end, color `#444466`

**Doubly LL node:**

```
┌───┬──────┬───┐
│ ← │  20  │ → │    three-part: prev, data, next
└───┴──────┴───┘
```

**Circular LL:** Last node's arrow curves back to first node with arc

**Animation — Traversal:**

- Each node highlights in sequence: accent color border + glow
- Duration: 300ms per node
- Previous node returns to normal before next highlights

**Animation — Insert:**

- New node fades in from opacity 0 at the correct position
- Arrow animates drawing (width grows from 0)
- Duration: 400ms total

---

### 5.3 Stack Visualization

**Stack container:** Vertical rectangle, bottom-aligned

```
    ┌─────────┐  ← TOP indicator label
    │  (40)   │  ← top element, accent border
    ├─────────┤
    │   30    │
    ├─────────┤
    │   20    │
    ├─────────┤
    │   10    │
    └─────────┘  ← BOTTOM
```

**Animation — Push:**

- New element slides down from top (translateY animation, 300ms)
- TOP label moves up

**Animation — Pop:**

- Top element slides up and fades out
- Duration: 300ms

---

### 5.4 Queue Visualization

**Queue display:** Horizontal, left to right

```
FRONT →  ┌────┐┌────┐┌────┐┌────┐  ← REAR
          │ 10 ││ 20 ││ 30 ││(40)│
          └────┘└────┘└────┘└────┘
```

**Animation — Enqueue:**

- New element slides in from the right, 300ms
- REAR label moves right

**Animation — Dequeue:**

- Front element slides left and fades out, 300ms
- All elements shift left (translateX), 200ms each

---

### 5.5 Tree Visualization

**Node Design:**

```
Normal:       ○ 50        circle radius: 28px
              border: 2px #2A2A3E
              fill: #1E1E2E
              text: #E8E8F0, JetBrains Mono 14px

Active:       ○(50)       border: 2px accent
              fill: accent at 20% opacity
              glow: 0 0 14px accent

Visited:      ○ 50        border: 2px #546E7A
              fill: #546E7A at 20% opacity
              text: #8888AA
```

**Edge (connecting lines):**

```
Normal edge:     1px #2A2A3E
Active edge:     2px accent color (when traversing)
```

**Tree canvas rendering:** Custom `QPainter` in `paintEvent()`

- Nodes positioned by recursive x/y calculation
- Root at top-center, children spread with calculated horizontal gap
- Canvas scrollable if tree grows large

**Animation — Insert:**

- Path from root to insertion point: each edge and node highlights in sequence (300ms per level)
- New node: scale animation from 0.0 to 1.0, 400ms, `QEasingCurve::OutBack` (slight bounce)

**Animation — AVL Rotation:**

- Nodes involved in rotation highlighted in amber
- Pause 400ms
- Nodes move to new positions with `QPropertyAnimation` on x/y, 500ms
- Tree redraws in new balanced state

---

### 5.6 Graph Visualization

**Node Design:**

```
Normal node:     ○ 0       circle, radius: 24px
                           border: 2px #2A2A3E, fill: #1E1E2E

BFS/DFS current: ○(0)      border: 2px accent (module red/blue)
                           glow: 0 0 16px accent

Visited node:    ○ 0       fill: #546E7A at 30%, border: #546E7A

Shortest path:   ○ 0       border: 2px #69F0AE (green), fill: green 20%
```

**Edges:**

```
Undirected:      ──────────    1px #2A2A3E
Directed:        ──────────►  1px #2A2A3E with arrowhead
Active edge:     ──────────    2px accent color
```

**Node placement:** Force-directed or manual grid layout. Minimum distance between nodes: 80px.

**BFS Animation:**

- Queue contents shown below canvas
- Each node visited: highlights in 300ms
- Edges traversed: animate in accent color
- Wave effect: current level stays accent, previous level fades to visited color

**Dijkstra Animation:**

- Distance table shown on right panel
- Current relaxation edge highlights in accent
- Updated distance shown with brief flash (yellow → settles to white)

---

### 5.7 Sorting Visualization

**Array bar/box design:**
Same as Array module element design.

**Comparison indicator:**

```
Comparing:  [ 10 ][ (30) ][ (20) ][ 40 ]
                   ↑──── comparing ────↑   label in accent
```

**Swap animation:**

- Two elements swap positions
- Animation: both move simultaneously with `QPropertyAnimation` on x
- Duration: 200ms, `QEasingCurve::InOutQuad`
- Color during swap: `#FF5370` (red border)
- After swap: return to normal color

**Sorted indicator:**

- Once an element is in its final position: border changes to `#69F0AE` (green)
- Remains green through rest of sort

**Pass indicator label:** "Pass 1 of 3" shown above array, updates between passes.

---

### 5.8 Hashing Visualization

**Hash Table Design:**

```
[0]  ─────────────
[1]  → ┌────┐ → ┌────┐ → NULL   (chaining)
       │  8 │   │ 15 │
       └────┘   └────┘
[2]  ─────────────
[3]  ─────────────
```

**Linear Probe table:**

```
┌────┬────┬────┬────┬────┬────┬────┐
│  _ │  8 │  9 │ 22 │  _ │  _ │  _ │
└────┴────┴────┴────┴────┴────┴────┘
  [0]  [1]  [2]  [3]  [4]  [5]  [6]
```

**Collision animation:**

- Probe sequence: each probed slot flashes amber briefly (150ms) before moving to next
- Inserted slot: flashes accent green when successfully placed

---

## 6. ANIMATION SYSTEM SUMMARY

| Animation               | Duration        | Easing     | Widget                         |
| ----------------------- | --------------- | ---------- | ------------------------------ |
| Array element shift     | 200ms           | OutQuad    | QPropertyAnimation (x)         |
| Array insert fade-in    | 300ms           | Linear     | QPropertyAnimation (opacity)   |
| LL traversal highlight  | 300ms per node  | Linear     | timer-driven repaint           |
| LL insert node appear   | 400ms           | OutBack    | scale animation                |
| Stack push slide-in     | 300ms           | OutQuad    | QPropertyAnimation (y)         |
| Stack pop slide-out     | 300ms           | InQuad     | QPropertyAnimation (y+opacity) |
| Queue enqueue slide     | 300ms           | OutQuad    | QPropertyAnimation (x)         |
| Tree path highlight     | 300ms per level | Linear     | timer-driven painter           |
| Tree node insert bounce | 400ms           | OutBack    | scale via painter              |
| AVL rotation            | 500ms           | InOutCubic | QPropertyAnimation (x,y)       |
| Graph BFS wave          | 300ms per node  | Linear     | timer-driven painter           |
| Sorting swap            | 200ms           | InOutQuad  | QPropertyAnimation (x)         |
| Hash probe flash        | 150ms           | Linear     | timer-driven fill              |
| Screen transition       | 250ms           | OutCubic   | QPropertyAnimation (opacity)   |
| Button hover            | 150ms           | Linear     | QPropertyAnimation (bg color)  |

---

## 7. BUTTON DESIGN SYSTEM

### 7.1 Button Types

**Primary (Run / Execute):**

```
Background: module accent color
Text: #0D0D0D (dark — high contrast)
Border: none
Border-radius: 10px
Padding: 12px 28px
Font: Segoe UI 14px SemiBold
Hover: accent at 80% brightness
```

**Secondary (Back / Reset):**

```
Background: transparent
Text: #E8E8F0
Border: 1px solid #2A2A3E
Border-radius: 10px
Padding: 12px 28px
Font: Segoe UI 14px Medium
Hover: background #1E1E2E
```

**Ghost (low emphasis):**

```
Background: transparent
Text: #8888AA
Border: none
Hover: text color → #E8E8F0
```

**Danger (Clear / Delete):**

```
Background: transparent
Text: #FF5370
Border: 1px solid #FF5370
Hover: background #FF5370 at 10%
```

---

## 8. ICON SYSTEM

All icons from **Qt's built-in QStyle** or custom SVG — monoline style, 20px:

| Module            | Icon                           |
| ----------------- | ------------------------------ |
| Linear Structures | `[]→[]→[]` (linked chain icon) |
| Stack & Queue     | stack of cards icon            |
| Trees             | branching tree icon            |
| Graph             | dots connected by lines        |
| Sorting           | ascending bars                 |
| Hashing           | `#` symbol                     |
| Performance       | bar chart icon                 |
| Back              | `←` arrow                      |
| Run               | `▶` play triangle              |
| Reset             | circular arrow                 |
| Exit              | `✕`                            |

Icon color: matches module accent or `#8888AA` for neutral

---

## 9. SCREEN TRANSITIONS

All screen transitions use `QStackedWidget` with:

- Fade out current screen: opacity 1→0, 125ms
- Swap widget
- Fade in new screen: opacity 0→1, 125ms
- Total: 250ms — smooth, not distracting

Breadcrumb always visible in top bar:

```
CDSIAS  →  Linear Structures  →  Array  →  Insert at Index
```

---

## 10. CLI DESIGN (CURRENT PHASE)

Until Qt is implemented, the CLI follows these same principles as closely as possible:

**Separator:** `------------------------------` (exactly 30 dashes)
**Headers:** `[MODULE] Operation: value` (uppercase module name in brackets)
**Spacing:** Blank line before and after separator blocks
**Alignment:** Data displayed in fixed-width columns using `setw()`
**Highlight:** `(val)` wrapping for active elements

**CLI Color (Windows ANSI):**

```cpp
// If Windows terminal supports ANSI:
#define ACCENT  "\033[96m"   // cyan = default accent
#define ERROR   "\033[91m"   // bright red
#define SUCCESS "\033[92m"   // bright green
#define WARNING "\033[93m"   // yellow
#define RESET   "\033[0m"
#define MUTED   "\033[90m"   // grey for labels
```

All color calls go through `visual.h` only.

---

## 11. RESPONSIVE CONSTRAINTS

| Constraint                   | Value                      |
| ---------------------------- | -------------------------- |
| Minimum window width         | 1100px                     |
| Minimum window height        | 720px                      |
| Sidebar width                | 220px (fixed)              |
| Step log panel width         | 280px (fixed)              |
| Visualization canvas         | fills remaining width      |
| Max tree canvas height       | 600px (scrollable beyond)  |
| Graph canvas size            | 700px × 500px (scrollable) |
| Array max elements displayed | 12 (scroll for more)       |

---

## 12. LOADING / EMPTY STATES

**Empty structure display:**

```
Visualization canvas shows:
  [ Empty — no elements ]
  in muted grey #444466, centered, JetBrains Mono 14px italic
```

**Operation running:**

```
"Running..." spinner or animated dots in accent color
Input fields and Run button disabled during animation
```

**Report empty:**

```
Performance Report shows:
  "No operations logged yet."
  in #8888AA centered
```
