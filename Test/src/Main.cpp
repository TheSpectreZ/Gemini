#include "Gemini.h"
#include <cstdint>
void Constructor()
{
	gem::Vectorf vector = { 4.f, 5.5f, 3.f, 11.31f };
	
	gem::Matrixf matrix2d = { {2,3,8}, {4,5, 6} };
	
	gem::Tensor3f matrix3d = { { {1,2,3,4}, {5,6,7,8}, { 9,10,11,12 } }, { {13,14,15,16}, {17,18,19,20}, {21,22,23,24} } };
	
	gem::Tensor4f matrix4d = { { { {1,2,3,4}, {5,6,7,8}, { 9,10,11,12 } }, { {13,14,15,16}, {17,18,19,20}, {21,22,23,24} }}, {{ {1,2,3,4}, {5,6,7,8}, { 9,10,11,12 } }, { {13,14,15,16}, {17,18,19,20}, {21,22,23,24} }} };
}

int main(int argc, char** argv)
{
	gem::Vectorf vector = { 4.f, 5.5f, 3.f, 11.31f };
	
	gem::Matrixf m1 = { {1,2}, {1,3} };

	auto m2 = m1 + 2;

	gem::Vectorf v1 = { 3.f, 3.f, 3.f };
	v1.normalize();

	return 0;
}