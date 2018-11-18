/**
  *   @file UI.cpp
  *   @brief Source file for class UI
  */


#include "UI.hpp"



/*  Class UI  */


/*  Constructor */

UI::UI(sf::RenderWindow &render_window, sf::RenderWindow &dialog, sf::Color backgroundcolor):
window(render_window), dialog_window(dialog), BackgoundColor(backgroundcolor)
{
  // TODO error checking
  messagebox.message_font.loadFromFile(FONT_ARIAL);
}


/*  Return window_status  */

int UI::getStatus ()
{
  return window_status;
}

/* Close active dialog */

void UI::CloseDialog()
{
  dialog_window.close();
  dialog_active = false;
  messagebox.active = false;
}


/*  Update UI based on sf::Events */

void UI::updateUI()
{
  sf::Event event;

  /* Poll window events ( if events aren't polled window will freeze, so events
    are also polled when dialog_window is active) */

  while( window.pollEvent(event) )
  {
    // Only update if there is no active dialog
    if (! dialog_active)
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
          window_status = false;
          break;

        case sf::Event::KeyPressed:
          HandleKeyPress(event);
          break;

        case sf::Event::MouseMoved:
          HandleMouseMove(event);
          break;

        case sf::Event::MouseButtonPressed:
          HandleMousePress(event);
          break;

        case sf::Event::Resized:
          HandleResize(event);
          break;

        default:
          std::cout << "Other sf::Event" << std::endl;
      }

      // Clear and display window
      window.clear(sf::Color(BackgoundColor));
      DrawUI();
      window.display();

    }

  }

  // Handle also possible dialog_window event loop
  if (dialog_active)
  {
    sf::Event event;
    while (dialog_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        CloseDialog();
      }
      else if (event.type == sf::Event::MouseButtonPressed)
      {
        HandleDialogMousePress(event);
      }
      else if (event.type == sf::Event::MouseMoved)
      {
        HandleDialogMouseMove(event);
      }
    }
    dialog_window.clear(sf::Color::White);
    DrawDialog();
    dialog_window.display();
  }

}

/* Draw to dialog_window */

void UI::DrawDialog()
{
  if (messagebox.active)
  {
    // Draw messagebox
    dialog_window.draw(messagebox.message);
    dialog_window.draw(messagebox.button);
  }
}

/* Handle window resizing */

void UI::HandleResize(sf::Event event)
 {
   // Reset view
   sf::FloatRect new_screen = sf::FloatRect(0, 0, event.size.width, event.size.height);
   window.setView(sf::View(new_screen));

 }

/* Handle dialog_window mouse press */

 void UI::HandleDialogMousePress(sf::Event event)
 {
   if (event.mouseButton.button == sf::Mouse::Left)
   {
     float x = (float) event.mouseButton.x;
     float y = (float) event.mouseButton.y;

     if (messagebox.active)
     {
       // if messagebox button is clicked, it calls UI::CloseDialog
       messagebox.button.checkClicked(x, y);
     }
   }
 }

 /* Handle dialog_window mouse movement */

 void UI::HandleDialogMouseMove(sf::Event event)
 {
   float x = (float) event.mouseMove.x;
   float y = (float) event.mouseMove.y;

   if (messagebox.active)
   {
     // Check if mouse hovers on the messagebox
     messagebox.button.tryActivate(x, y);
   }
 }


/*  Create and start showing a messagebox */

 void UI::ShowMessageBox(std::string message, sf::Vector2i position)
 {
   float button_width = 40;
   float button_height = 30;
   messagebox.active = true;
   messagebox.message = sf::Text(message, messagebox.message_font, 14);
   messagebox.button = Button("Ok", sf::Color::White, button_width, button_height);

   messagebox.button.setTextColor(sf::Color::Black);
   messagebox.button.setOutline(1, sf::Color::Black);
   messagebox.button.setActiveColor(sf::Color(0, 0, 200, 50));

   sf::Text& button_text = messagebox.button.getText();
   button_text.setStyle(sf::Text::Regular);

   // Bind CloseDialog to Button click_action
   messagebox.button.setClickFunction( std::bind(&UI::CloseDialog, this) );

   // Get Text rect size
   float width = messagebox.message.getLocalBounds().width;
   float height = messagebox.message.getLocalBounds().height;
   unsigned x = (unsigned) width + button_width + 30; // Modify this if needed
   unsigned y = (unsigned) height + button_height + 50; // Modify this if needed

   // Create messagebox to the dialog_window
   dialog_window.create(sf::VideoMode(x, y), "Information", sf::Style::Close);
   dialog_window.setPosition(position);

   messagebox.message.setPosition(30, 20);
   messagebox.button.setPosition(x - (button_width + 30), y - (button_height + 10));

   messagebox.message.setFillColor(sf::Color::Black);

   // Change dialog_window status
   dialog_active = true;

 }
