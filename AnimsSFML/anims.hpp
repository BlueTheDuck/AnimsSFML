#ifndef ANIMS
#define ANIMS

#pragma once

#include <string>
#include <deque>

#ifdef _DEBUG 
#include <iostream>
#endif

#include <SFML\Graphics.hpp>

#define ROT 1//Rotation
#define POS 2//Position
#define ABS 16//Absolute modifier

namespace as {
	struct frame {
		int type = 0;
		float* args = new float[2];//For POS
		float arg = 0;//For ROT
	};

	class KeyFrames {
	public:
		frame * frames;
		int totalFrames = 0;
		//char ** r = new char*[2];
		//Member initialization
		KeyFrames() {}
		void ini( int frameAmount ) {
			totalFrames = frameAmount;
			frames = new frame[totalFrames];
			#ifdef _DEBUG
			std::cout << "Object initialized with " << totalFrames << " frames" << std::endl;
			#endif
		}
		void set( int dir, int type, float args[2] );
		void set( int dir, int type, float arg );
		frame* get( int dir );
	};

	template <typename T>
	class Animation {
		T object;
		sf::Vector2<float> iniPos;
		int iniRot;
		static unsigned int initialized;//Objects initialized
	public:
		//static Animation<T> * Animations;
		static std::deque<void*> Animations;
		unsigned int ID;//ID of the new object
		int actFrame = 0, frames = 1;
		float frameRate = 27;
		KeyFrames kFrames;
		Animation( T x, int frameAmount ) {
			object = x;
			frames = frameAmount;
			kFrames.ini( frameAmount );
			iniPos = { ( *object ).getPosition().x, ( *object ).getPosition().y };
			iniRot = ( *object ).getRotation();
			ID = initialized;
			//Animations[ID] = this;
			if( Animations.size() <= ID ) {
				Animations.push_front( this );
			} else {
				Animations.at( ID ) = this;
			}
			initialized++;
			#ifdef _DEBUG
			std::cout << "Initialized instance with ID " << ID << " at the addrs " << reinterpret_cast<unsigned int>( this ) << std::endl;
			#endif // _DEBUG

		}
		void Animation::Move( sf::Vector2<int> toPos, bool absolute, unsigned int from = 0, unsigned int to = 27 );
		void Animation::Rotate( int angle, bool absolute, int from, int to );
		void Animation::ProcessFrame( int frm );
		#ifdef _DEBUG
		void Animation::printDebug() {
			std::cout << "Animation instance with ID " << ID << " of " << initialized << std::endl;
			for( int i = 0; i < frames; i++ ) {
				std::cout << "Frame: " << i << " Type: " << ( kFrames.get( i )[0] ).type << std::endl;
			}
			std::cout << "\nActual frame: " << actFrame << "/" << frames << " at " << frameRate << "fps\n";
		}
		#endif // _DEBUG
	};

	/*void frameControllerThread() {

	}*/
}


template <typename T> unsigned int as::Animation<T>::initialized = 0;
template <typename T> std::deque<void*> as::Animation<T>::Animations = std::deque<void*>(1);


#endif // !ANIMS