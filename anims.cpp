#ifndef ANIMS
#include "anims.hpp"
#endif // !ANIMS

void AnimsSFML::KeyFrames::set( int dir, int type, float args[2] ) {
	if( dir >= totalFrames || dir < 0 ) {
		throw std::invalid_argument( "frame* KeyFrames::get( int dir )\n'dir' has to be between 0 and " + totalFrames );
	}
	#ifdef _DEBUG
	std::cout << "Setting frame " << dir << std::endl;
	#endif // _DEBUG
	frames[dir].args = args;
	frames[dir].type = type;
}
void AnimsSFML::KeyFrames::set( int dir, int type, float arg ) {
	if( dir >= totalFrames || dir < 0 ) {
		throw std::invalid_argument( "frame* KeyFrames::get( int dir )\n'dir' has to be between 0 and " + totalFrames );
	}
	#ifdef _DEBUG
	std::cout << "Setting frame " << dir << std::endl;
	#endif // _DEBUG
	frames[dir].arg = arg;
	frames[dir].type = type;
}
AnimsSFML::frame* AnimsSFML::KeyFrames::get( int dir ) {
	if( dir >= totalFrames || dir < 0 ) {
		throw std::invalid_argument("frame* KeyFrames::get( int dir )\n'dir' has to be between 0 and "+totalFrames);
	}
	return &frames[dir];
}

template <typename T>
void AnimsSFML::Animation<T>::Move( sf::Vector2<int> toPos, bool absolute, unsigned int from = 0, unsigned int to = 27 ) {

	iniPos = { ( *object ).getPosition().x, ( *object ).getPosition().y };
	int framesRange = to - from;

	sf::Vector2<float> steps;
	steps.x = toPos.x / framesRange;
	steps.y = toPos.y / framesRange;
	for( int i = from; i < to; i++ ) {
		float* frm = new float[2];
		frm[0] = steps.x;
		frm[1] = steps.y;
		if( absolute ) {
			frm[0] *= i;
			frm[1] *= i;
			frm[0] += iniPos.x;
			frm[1] += iniPos.y;
			kFrames.set( i, POS + ABS, frm );
		} else {
			kFrames.set( i, POS, frm );
		}
	}
	cout << steps.x;
}
template <typename T>
void AnimsSFML::Animation<T>::Rotate( int angle, bool absolute, int from, int to ) {
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
template <typename T>
void AnimsSFML::Animation<T>::ProcessFrame( int frm ) {
	frame* f = kFrames.get( frm );
	#ifdef _DEBUG
	/*std::cout << "\nProcessing frame " << frm << std::endl <<
		" Type: " << ( *f ).type << std::endl;
	if( ( *f ).type&POS )
		std::cout << " Args: " << ( *f ).args[0] << "&" << ( *f ).args[1];
	else
		std::cout << " Arg: " << ( *f ).arg;
		*/
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
	actFrame = actFrame == ( frames - 1 )?0:actFrame + 1;
}

