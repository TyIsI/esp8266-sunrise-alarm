#ifndef ANIMATION_H
#define ANIMATION_H

// Interval in ms to update animation
unsigned long lastAnimationUpdate = 0;

// Value of millis() when an animation starts.
// (used as basis for animation timeline)
unsigned long animationStartTime = 0;

// Which animation is presently playing (if any)
int animationState = ANIM_STATE_OFF;

#endif