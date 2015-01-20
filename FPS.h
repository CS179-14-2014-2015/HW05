#ifndef FPS_H
#define FPS_H

class FPS
{
	protected:
		unsigned int m_fps;
		unsigned int m_fpscount;
		unsigned int m_start;
		unsigned int m_fpsinterval;
		//Interval m_fpsinterval;

	public:
		FPS();
		~FPS(){};

		void update();
		unsigned int get() const;
};

#endif