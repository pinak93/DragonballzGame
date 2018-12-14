#include <iostream>
#include <SDL.h>
#include "imageFactory.h"

class RenderContext{
public:
  static RenderContext& getInstance();
  ~RenderContext();
  SDL_Window* getWindow() const { return window; }
  SDL_Renderer* getRenderer() const { return renderer; }

	 Image* getImage(const std::string& n) { 
    return factory.getImage(n);
  }
  std::vector<Image*> getImages(const std::string& n) {
    return factory.getImages(n);
  }
	
 Image* getImageL(const std::string& n)  {
    return factory.getCustomImageL(n);
  }
	 Image* getImageR(const std::string& n)  {
    return factory.getCustomImageR(n);
  }
	
private:
  
  SDL_Window* window;
  SDL_Renderer* renderer;

  ImageFactory& factory;

  SDL_Window* initWindow();
  SDL_Renderer* initRenderer();
  RenderContext();
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};
