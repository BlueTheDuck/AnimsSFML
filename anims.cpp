#include "anims.hpp"

void KeyFrames::set( int dir, int type, float args[2] ) {
	std::cout << "Setting frame " << dir << std::endl;
	frames[dir].args = args;
	frames[dir].type = type;
}
void KeyFrames::set( int dir, int type, float arg ) {
	std::cout << "Setting frame " << dir << std::endl;
	frames[dir].arg = arg;
	frames[dir].type = type;
}
frame* KeyFrames::get( int dir ) {
	if( dir < totalFrames && dir >= 0 ) {
		return &frames[dir];
	}
}

template <typename T>
void Animation<T>::Move( sf::Vector2<int> toPos, bool absolute, int from = 0, int to = 27 ) {

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