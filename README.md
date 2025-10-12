## Work Breakdown (Files & Responsibilities)

| File | Role | Description |
|------|------|--------------|
| **Main.cpp** | **Application Entry Point** | Initializes JUCE and starts the app by creating a `MainComponent` window. Handles startup and shutdown logic only. |
| **MainComponent.h / .cpp** | **App Layout Controller** | The main container of the application. Manages the layout and displays the player interface. It can hold one or more `PlayerGUI` components. |
| **PlayerAudio.h / .cpp** | **Audio Logic Module (Backend)** | Responsible for all audio operations — loading files, playing, pausing, stopping, volume control, speed control, etc. Uses JUCE classes such as `AudioTransportSource`, `AudioFormatReaderSource`, and `AudioFormatManager`. |
| **PlayerGUI.h / .cpp** | **User Interface Module (Frontend)** | Builds the visual interface (buttons, sliders, labels). Handles user interactions (Play, Stop, Load, Volume). Calls the corresponding functions in `PlayerAudio` to execute actions. |

---
## File Relationships
- **Main.cpp:** Launches the app.  
- **MainComponent:** Hosts the GUI components.  
- **PlayerGUI:** Manages buttons/sliders and interacts with the user.  
- **PlayerAudio:** Executes the actual sound playback and logic.
