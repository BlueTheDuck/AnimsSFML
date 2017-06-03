#pragma once

#ifndef ANIMS
#define ANIMS

#include <string>

#ifdef _DEBUG 
#include <iostream>
#endif

#include <SFML\Graphics.hpp>

#define ROT 1//Rotacion
#define POS 2//Posicion
#define ABS 16//Modificador absoluto

struct frame {
	int type = 0;
	//std::string args = "";
	float* args = new float [2];//For POS
	float arg = 0;//For ROT
};

class KeyFrames {
	public:
		frame * frames;
		int totalFrames = 0;
		//char ** r = new char*[2];
		//Member initialization
		KeyFrames(int frameAmount) {
			totalFrames = frameAmount;
			frames = new frame[totalFrames];
		}
		KeyFrames() {
			totalFrames = 27;
			frames = new frame[totalFrames];
		}
		void set( int dir, int type, float args[2] );
		void set( int dir, int type, float arg/*std::string args*/ );
		frame* get( int dir );
		/*void set(int dir,char act,char arg) {
			actions[dir] = act;
			args[dir] = arg;
		}
		char** operator[](int dir) {
			//char * r = new char[2];
			r[0] = &actions[dir];
			r[1] = &args[dir];
			//std::cout << "[]";
			return r;
		}
		char** operator=( const char** arr ) {
			std::cout << arr;
			return r;
		}*/
		/*KeyFrames& operator=( const KeyFrames& x ) {
			r[0] = actions[dir];
			r[1] = args[dir];
			std::cout << "=";
			return r;
		}*/
};

template <typename T>
class Animation {
		T object;
		sf::Vector2<float> iniPos;
		int iniRot;
	public:
		int actFrame = 0, frames = 1;
		float frameRate = 27;
		KeyFrames kFrames;
		Animation(T x,int frameAmount) {
			object = x;
			frames = frameAmount;
			KeyFrames kFrames(frameAmount);
			iniPos = { ( *object ).getPosition().x, ( *object ).getPosition().y };
			iniRot = ( *object ).getRotation();
		}
		void Animation::Move( sf::Vector2<int> toPos, bool absolute, int from = 0, int to = 27 );
		/*void Animation::Rotate( int angle, bool absolute ) {//Shorthand
			iniRot = ( *object ).getRotation();
			float step;
			step = (float)angle / frameRate;
			for( int i = 0; i < frames; i++ ) {
				float frm = step;
				if( absolute ) {
					frm *= i;
					frm += iniRot;
					kFrames.set( i, ROT + ABS, frm );
				} else {
					kFrames.set( i, ROT, frm );
				}
			}
			//this::Rotate( angle, absolute, 0, frames);
		}*/
		void Animation::Rotate( int angle, bool absolute, int from, int to ) {
			//if( from > to || from >= frames || to >= frames ) return;//If arguments are invalid, exit

			int framesRange = to - from;
			iniRot = ( *object ).getRotation();
			float step;
			step = (float)angle / framesRange;
			for( int i = from; i < to; i++ ) {
				float frm = step;
				if( absolute ) {
					frm *= i;
					frm += iniRot;
					kFrames.set( i, ROT + ABS, frm );
				} else {
					kFrames.set( i, ROT, frm );
				}
			}
		}
		void Animation::ProcessFrame( int frm ) {
			frame* f = kFrames.get( frm );
			#ifdef _DEBUG
			std::cout << "Processing frame " << frm << std::endl <<
				" Type: " << ( *f ).type << std::endl;
			if( ( *f ).type&POS ) 
				std::cout << " Args: " << ( *f ).args[0] << "&" << ( *f ).args[1];
			else
				std::cout << " Arg: " << ( *f ).arg;

			#endif // _DEBUG
			if( ( *f ).type&POS ) {
				if( ( *f ).type&ABS ) {//Absolute duh...
					( *object ).setPosition( ( *f ).args[0], ( *f ).args[1] );
				} else {//Relative
					( *object ).setPosition( iniPos.x + ( *f ).args[0], iniPos.y + ( *f ).args[1] );
				}
			} else if( ( *f ).type&ROT ) {
				if( ( *f ).type&ABS ) {
					( *object ).setRotation( ( *f ).arg );
				} else {
					( *object ).setRotation( ( *f ).arg + ( *object ).getRotation() );
				}
			}
			if( actFrame == frames - 1 ) {
				//animationEnd();
			}
			actFrame = actFrame == ( frames - 1 )?0:actFrame + 1;
		}
		#ifdef _DEBUG
		void Animation::printDebug() {
			//std::cout << kFrames.get( 0 )[1];
			for( int i = 0; i < frames; i++ ) {
				std::cout << "Frame: " << i << " Type: " << ( *kFrames.get( i ) ).type << std::endl;
			}
			std::cout << "\nActual frame: " << actFrame << "/" << frames << " at " << frameRate << "fps\n";
		}
		#endif // _DEBUG
		//void Animation::animationEnd();
		//void Animation::Animate( int animType, )
};

#endif // !ANIMS