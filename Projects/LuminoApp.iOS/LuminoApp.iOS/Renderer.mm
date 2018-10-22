
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#import "Renderer.h"

@implementation Renderer
{
	EAGLContext* _eaglContext;
}

-(nonnull instancetype)initWithOpenGLKitView:(nonnull GLKView *)view;
{
	self = [super init];
	if(self)
	{
		// Create OpenGL context
		_eaglContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
		[EAGLContext setCurrentContext:_eaglContext];
		view.context = _eaglContext;
		
        // Create badkend FBO
        [view bindDrawable];
        GLint backendFBO;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &backendFBO);
		
		GLint backendWidth = 0;
		GLint backendHeight = 0;
		glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backendWidth);
		glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backendHeight);
		
		ln::iOSPlatformInterface::nativeInitialize(backendWidth, backendHeight);
		ln::detail::SwapChainHelper::setBackendBufferSize(ln::Engine::mainWindow()->swapChain(), backendWidth, backendHeight);
        ln::detail::SwapChainHelper::setOpenGLBackendFBO(ln::Engine::mainWindow()->swapChain(), backendFBO);
		
		[view setNeedsDisplay];
		[view enableSetNeedsDisplay];
	}
	
	return self;
}

- (void)glkView:(nonnull GLKView *)view drawInRect:(CGRect)rect
{
	ln::iOSPlatformInterface::nativeUpdateFrame();
}

@end
