class Bullet{

public:

	//constructors
	Bullet();
	Bullet(GLFWwindow* window, float x, float y, int* colorPrim, int* colorSec);

	~Bullet();

	//update and state setting
	void update(const double& frameDiff);
	void setState(bool up, bool down, bool left, bool right);

	//actions
	void shoot();
	void move();

	//drawing
	void drawPlayer();

private:
	float speed = 2.0;

}