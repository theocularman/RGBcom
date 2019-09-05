/*
   Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com> and Leka <http://weareleka.com>

   This file is part of Moti, a spherical robotic smart toy for autistic children.

   Moti is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Moti is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Moti. If not, see <http://www.gnu.org/licenses/>.
   */

/**
 * @file Color.cpp
 * @author Ladislas de Toldi
 * @version 1.0
 */
 
#include "Arduino.h"
#include "Color.h"

/*
 * @brief Default constructor, sets R, G, B to be equal to 0
 */
Color::Color() {
	_r = _g = _b = 0;
}

/*
 * @brief R, G, B constructor (0-255)
 * @param r the red intensity of the color
 * @param g the green intensity of the color
 * @param b the blue intensity of the color
 */
Color::Color(uint8_t r, uint8_t g, uint8_t b) {
	_r = r;
	_g = g;
	_b = b;
}

/**
 * @brief Reads the RGB values (0-255)
 * @param r pointer that will receive the content of the red intensity
 * @param g pointer that will receive the content of the green intensity
 * @param b pointer that will receive the content of the blue intensity
 */
void Color::getRGB(uint8_t* r, uint8_t* g, uint8_t* b) {
	*r = _r;
	*g = _g;
	*b = _b;
}

/**
 * @brief Getter method to get the red intensity of the color (0-255)
 * @return the red intensity
 */
uint8_t Color::getR(void) {
	return _r;
}

/**
 * @brief Getter method to get the green intensity of the color (0-255)
 * @return the green intensity
 */
uint8_t Color::getG(void) {
	return _g;
}

/**
 * @brief Getter method to get the blue intensity of the color (0-255)
 * @return the blue intensity
 */
uint8_t Color::getB(void) {
	return _b;
}

/**
 * @brief Reads the HSV values
 * @param hue pointer that will receive the content of the hue
 * @param saturation pointer that will receive the content of the saturation
 * @param value pointer that will receive the content of the value
 */
void Color::getHSV(uint16_t* hue, float* saturation, float* value) {
	*hue = _hue;
	*saturation = _saturation;
	*value = _value;
}

/**
 * @brief Getter method to get the hue of the color
 * @return the hue
 */
uint16_t Color::getHue(void) {
	return _hue;
}

/**
 * @brief Getter method to get the saturation of the color
 * @return the saturation
 */
float Color::getSaturation(void) {
	return _saturation;
}

/**
 * @brief Getter method to get the value of the color
 * @return the value
 */
float Color::getValue(void) {
	return _value;
}

double __mod(double a, double b) {
	double r = fmod(a, b);

	return r < 0.f ? r + b : r;
}

/**
 * @brief Setter method to set the red, green and blue intensities of the color (0-255)
 * @param r the new red intensity of the color
 * @param g the new green intensity of the color
 * @param b the new blue intensity of the color
 */
void Color::setRGB(uint8_t r, uint8_t g, uint8_t b) {
	float new_r = (float)r / 255.f;
	float new_g = (float)g / 255.f;
	float new_b = (float)b / 255.f;

	float c_max = max(new_r, max(new_g, new_b));
	float c_min = min(new_r, min(new_g, new_b));

	float delta = c_max - c_min;

	if (c_max == new_r)
		_hue = (uint16_t)(60.f * __mod((new_g - new_b) / delta, 6.f));
	else if (c_max == new_g)
		_hue = (uint16_t)(60.f * (((new_b - new_r) / delta) + 2.f));
	else
		_hue = (uint16_t)(60.f * (((new_r - new_g) / delta) + 4.f));

	if (c_max == c_min)
		_saturation = 0.f;
	else
		_saturation = delta / c_max;

	_value = c_max;

	_r = r;
	_g = g;
	_b = b;
}

/**
 * @brief Setter method to set the hue, saturation and value of the color (See http://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB)
 * @param hue the new hue of the color
 * @param b the new saturation of the color
 * @param g the new value of the color
 */
void Color::setHSV(uint16_t hue, float saturation, float value) {
	float c = value * saturation;

	uint16_t h = hue / 60;

	float x = c * (1.f - abs((float)(h % 2) - 1.f));
	float int_c = c;

	float r = 0.f;
	float g = 0.f;
	float b = 0.f;

	switch (h) {
		case 0:
			r = int_c;
			g = x;
			break;

		case 1:
			r = x;
			g = int_c;
			break;

		case 2:
			g = c;
			b = x;
			break;

		case 3:
			g = x;
			b = c;
			break;

		case 4:
			r = x;
			b = c;
			break;

		case 5:
			r = c;
			b = x;
			break;
	}

	float m = value - c;

	_r = (uint8_t)(r + m);
	_g = (uint8_t)(g + m);
	_b = (uint8_t)(b + m);

	_hue = hue;
	_saturation = saturation;
	_value = value;
}

/**
 * @brief Returns a random color
 * @return the color
 */
Color Color::randomColor(void) {
	return Color(random(0, 255), random(0, 255), random(0, 255));
}

// operateur ==
 bool Color::isEgal(Color const& colora) const
 {
     return (_r== colora._r && _g== colora._g && _b== colora._b);  // test si c'est egal
 }

// bool Color::EgalEgal(Color const& a, Color const& b)
// {
//     if (a.Color::getR()==b.Color::getR() && a.Color::getG()==b.Color::getG() && a.Color::getB()==b.Color::getB() ){
//     	return TRUE;
//     }
//     else {
//     	return FALSE;
//     }
// }


/**
 * @brief Set basic color values
 */
const Color Color::Black = Color(0, 0, 0);
const Color Color::White = Color(255, 255, 255);
const Color Color::RedPure = Color(255, 0, 0);
const Color Color::GreenPure = Color(0, 255, 0);
const Color Color::BluePure = Color(0, 0, 255);
const Color Color::DarkRed = Color(186, 48, 42);
const Color Color::LightRed = Color(222, 63, 89);
const Color Color::Purple = Color(165, 67, 188);
const Color Color::LightBlue = Color(95, 184, 224);
const Color Color::LightPink = Color(255, 232, 225);
const Color Color::Yellow = Color(250, 211, 51);
const Color Color::DarkYellow = Color(244, 174, 51);
const Color Color::Orange = Color(240, 143, 51);
const Color Color::DarkOrange = Color(239, 134, 59);
const Color Color::LightGreen = Color(216, 255, 56);
