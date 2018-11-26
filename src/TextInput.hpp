/**
  *   @file TextInput.hpp
  *   @brief Header for class TextInput
  */

#pragma once


/*  Includes */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>
#include <string>
#include <set>
#include <vector>


/**
  *   @class TextInput
  *   @brief Create text inputs
  *   @details Used in LevelEditor during saving level
  *   @remark Supports currently only Courier (monospaced) font
  */
class TextInput: public sf::Drawable
{
  public:

    /**
      *   @brief Empty constructor
      */
      TextInput();

    /**
      *   @brief Standard constructor
      */
      TextInput(float x, float y, float width, float height);

    /**
      *   @brief Copy constructor
      *   @param text_input Reference TextInput
      *   @remark Outline style is not copied !
      */
      TextInput(const TextInput &text_input);

    /**
      *   @brief Assignment overload
      *   @param text_input Reference TextInput
      *   @return Returns copy of text_input
      *   @remark Outline style is not copied !
      */
      TextInput& operator=(const TextInput &text_input);

    /**
      *   @brief Set position
      *   @param x x coordinate
      *   @param y y coordinate
      */
      void setPosition(float x, float y);

    /**
      *   @brief Try to activate /deactivate TextInput
      *   @param x x coordinate
      *   @param y y coordinate
      *   @remark If TextInput is activated, deactivates it
      */
      bool tryActivate(float x, float y);

    /**
      *   @brief Add char to TextInput if the input is active
      *   @param new_char UTF-32 coded char
      */
      void addChar(char32_t new_char);

    /**
      *   @brief Deactivate TextInput
      */
      void deactivate();

    /**
      *   @brief Set outline color and thickness
      *   @param color Outline color
      *   @param thickness Outline thickness
      */
      void setOutline(sf::Color color, float thickness);

    /**
      *   @brief Set text color
      *   @param color New text_color
      */
      void setTextColor(sf::Color color);

    /**
      *   @brief Removes previous char from the input
      */
      void removeChar();

    /**
      *   @brief Start / stop using strict_sanitization
      *   @param activate If true strict_sanitization is activated
      */
      void enableStrictSanitization(bool activate);

    /**
      *   @brief Get input text
      *   @return Returns input string
      */
      std::string getInputText();


  protected:

    /**
      *   @brief Draw TextInput
      *   @details Defined as a pure virtual function in sf::Drawable
      *   @param target RenderTarget target
      *   @param states RenderStates
      */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    /**
      *   @brief Highlight current char
      */
      void HighlightCurrent();

    /**
      *   @brief Create input_sanitization set
      */
      void CreateSanitizationSet();

    /**
      *   @brief Do basic initializations
      */
      void CreateTextInput();


    std::string input;
    sf::Text text;
    sf::Font font;
    float width;
    float height;
    float x;
    float y;
    sf::Rect<float> rect;
    sf::RectangleShape frame;
    sf::RectangleShape highlight;
    sf::Color active_color;
    sf::Color std_color;
    sf::Color text_color;
    bool active = false;
    unsigned font_size = 14;
    int line = 1;
    std::vector<unsigned> chars_on_lines;
    std::set<char32_t> input_sanitization;
    std::set<char32_t> input_sanitization_strict;
    bool strict_sanitization = false;

};
