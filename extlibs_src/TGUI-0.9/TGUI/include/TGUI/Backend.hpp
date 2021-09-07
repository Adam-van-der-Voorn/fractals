/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2021 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_BACKEND_HPP
#define TGUI_BACKEND_HPP

#include <TGUI/Font.hpp>
#include <TGUI/Event.hpp>
#include <TGUI/Cursor.hpp>
#include <cstdint>
#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class GuiBase;
    class BackendBase;
    class BackendFontBase;
    class BackendTextBase;
    class BackendTextureBase;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Checks whether the backend differs from a nullptr
    /// @return Has setBackend been called with a valid backend?
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool isBackendSet();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Changes the global backend
    ///
    /// This function is automatically called when the first Gui object is created. When all Gui objects have been destructed,
    /// this function will be called again with a nullptr as parameter to destroy all global resources.
    ///
    /// If you want to use TGUI functionality before creating a Gui object then you should call this function directly.
    ///
    /// @warning When calling the function directly, it has to be the first call to TGUI and you must call setBackend(nullptr)
    ///          before the end of the main() function.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void setBackend(std::shared_ptr<BackendBase> backend);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the global backend
    ///
    /// @return Global backend
    ///
    /// @warning This function will assert if no backend has been created yet or after it has been destroyed.
    /// @see isBackendSet()
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API std::shared_ptr<BackendBase> getBackend();



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for the backend
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API BackendBase
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        BackendBase() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // The object cannot be copied
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        BackendBase(const BackendBase&) = delete;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // The object cannot be copied
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        BackendBase& operator=(const BackendBase&) = delete;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~BackendBase() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Informs the backend whether it should destroy itself when the last Gui is detached from it.
        ///
        /// @param destroyOnDetatch  Should setBackend(nullptr) be called when there are no more Gui objects left?
        ///
        /// This function will be called with "true" as parameter if the Backend is created by a Gui object.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setDestroyOnLastGuiDetatch(bool destroyOnDetatch);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Informs the backend that a new gui object has been created.
        /// @param gui  Newly created gui
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void attachGui(GuiBase* gui) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Informs the backend that a gui object is being destroyed.
        /// @param gui  Gui object that is about to be deconstructed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void detatchGui(GuiBase* gui) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates and returns the default font for all widgets
        /// @return Default font
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Font createDefaultFont() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new font object
        /// @return Font that is specific to the backend
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<BackendFontBase> createFont() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new text object
        /// @return Text that is specific to the backend
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<BackendTextBase> createText() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new texture object
        /// @return Texture that is specific to the backend
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<BackendTextureBase> createTexture() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the look of a certain mouse cursor by using a bitmap
        ///
        /// @param type    Cursor that should make use of the bitmap
        /// @param pixels  Pointer to an array with 4*size.x*size.y elements, representing the pixels in 32-bit RGBA format
        /// @param size    Size of the cursor
        /// @param hotspot Pixel coordinate within the cursor image which will be located exactly at the mouse pointer position
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setMouseCursorStyle(Cursor::Type type, const std::uint8_t* pixels, Vector2u size, Vector2u hotspot) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the look of a certain mouse cursor back to the system theme
        ///
        /// @param type  Cursor that should no longer use a custom bitmap
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void resetMouseCursorStyle(Cursor::Type type) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the mouse cursor when the mouse is on top of the window to which the gui is attached
        ///
        /// @param gui   The gui that represents the window for which the mouse cursor should be changed
        /// @param type  Which cursor to use
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setMouseCursor(GuiBase* gui, Cursor::Type type) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens the virtual keyboard on Android and iOS
        /// @param inputRect Part of the screen where the text input is located
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void openVirtualKeyboard(const FloatRect& inputRect) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the virtual keyboard on Android and iOS
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void closeVirtualKeyboard() = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks the state for one of the modifier keys
        ///
        /// @param modifierKey  The modifier key of which the state is being queried
        ///
        /// @return Whether queries modifier key is being pressed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool isKeyboardModifierPressed(Event::KeyModifier modifierKey) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the contents of the clipboard
        ///
        /// @param contents  New contents of the clipboard
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setClipboard(const String& contents);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the contents of the clipboard
        ///
        /// @return Clipboard contents
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual String getClipboard() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Uses the AssetManager on Android to read a file and return its contents
        ///
        /// @param filename  Path to the file to read
        /// @param fileSize  Size of the file, to be filled in by this function if loading succeeds (untouched on failure)
        ///
        /// @return File contents if the file was successfully read, or a nullptr on failure or if platform isn't Android.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::unique_ptr<std::uint8_t[]> readFileFromAndroidAssets(const String& filename, std::size_t& fileSize) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        bool m_destroyOnLastGuiDetatch = false;
        String m_clipboardContents;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BACKEND_HPP
