#ifndef VEC_H
#define VEC_H

class vec
{
	public:
		vec();
		vec(double x, double y);

		~vec();

		void addVector ( const vec & v, double dt = 0 );
		void subtractVector ( const vec & v );
		void scaleVector ( double multiplier );
		void normalizeVector();

		double getLengthOfVector() const;
		double getX() const;
		double getY() const;
		double getPrevX() const;
		double getPrevY() const;
		void setXCoordinate( double num );
		void setYCoordinate( double num );
		double x, y;
		double prevx,prevy;

};

#endif