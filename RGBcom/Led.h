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

#ifndef LEKA_MOTI_CLASS_LED_H_
#define LEKA_MOTI_CLASS_LED_H_

//mode definitions
#define COMMON_ANODE 1
#define COMMON_CATHODE 0

/**
 * @file Led.h
 * @author Ladislas de Toldi
 * @version 1.0
 */

#include "Arduino.h"
#include "Color.h"

/**
 * @class Led
 * @brief Led library gathers all the LED functions for Moti.
 */

class Led {
	public:
		Led();
		Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, bool modeFlag);
		Led(uint8_t redPin, uint8_t greenPin, uint8_t bluePin, Color colorValue, bool modeFlag);

		void shine(void);
		void shine(Color colorValue);
		void shine(uint8_t redValue, uint8_t greeValue, uint8_t blueValue);

		void turnOff(void);

		Color getColor(void);
		void setColor(Color colorValue);

	protected:
    bool commonMode;
		uint8_t _redPin, _greenPin, _bluePin;
		Color _colorValue;
};

#endif
