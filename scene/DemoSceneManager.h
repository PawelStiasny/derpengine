#include "../util/SceneManager.h"

#include "../util/Settings.h"
#include "../core/Camera.h"
#include "../scene/Skybox.h"
#include "../scene/Terrain.h"
#include "../scene/Mech.h"
#include "../animations/CameraTracking.h"
#include "../animations/MechWalk.h"

class DemoSceneManager : public SceneManager
{
public:
	DemoSceneManager(Settings *settings);
	virtual void handleInput(InputState *st);

private:
	Camera *mechcam;
	Light *sun;
	Terrain *terrain;
	Mech *mech;
	CameraTracking *scene_rot;
	MechWalk *walk_animation;
};
