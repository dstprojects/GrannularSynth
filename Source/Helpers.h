/*
  ==============================================================================

    Helpers.h
    Created: 6 Nov 2019 6:27:13pm
    Author:  Alexis Uriel Guerrero Montoya

  ==============================================================================
*/

#pragma once

const int grainEnvelopeSize = 1024;
const float myPI = 3.14159265359;
const float my2PI = 6.28318530718;

inline float lerp(float v0, float v1, float t){
    return (1 - t) * v0 + (t * v1);
}
