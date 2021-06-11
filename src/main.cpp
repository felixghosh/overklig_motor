#include <iostream>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

Display *dis;
int screen;
Window win;
GC gc;
unsigned long black, white;


void init_x() {
	/* get the colors black and white (see section for details) */

	/* use the information from the environment variable DISPLAY 
	   to create the X connection:
	*/
	dis = XOpenDisplay((char *)0);
	screen = DefaultScreen(dis);
	black = BlackPixel(dis, screen),
	white = WhitePixel(dis, screen);

	/* once the display is initialized, create the window.
	   This window will be have be 200 pixels across and 300 down.
	   It will have the foreground white and background black
	*/
	win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 100, 100, 640, 480, 5, black, white);

	/* here is where some properties of the window can be set.
	   The third and fourth items indicate the name which appears
	   at the top of the window and the name of the minimized window
	   respectively.
	*/
	XSetStandardProperties(dis,win,"test window", "hello", None, NULL, 0, NULL);

	/* this routine determines which types of input are allowed in
	   the input.  see the appropriate section for details...
	*/
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

	/* create the Graphics Context */
	gc = XCreateGC(dis,win,0,0);

	/* here is another routine to set the foreground and background
	   colors _currently_ in use in the window.
	*/
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	

	/* clear the window and bring it on top of the other windows */
	XClearWindow(dis, win);
	XMapRaised(dis, win);
}

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis, win);
	XCloseDisplay(dis);
	exit(1);
}

void redraw() {
	std::cout << "pls redraw" << std::endl;
}

void run_x() {
	XEvent event;
	KeySym key;
	char text[255];

	/* main loop*/
	while(true){
		/* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/
		XNextEvent(dis, &event);

		if(event.type == Expose && event.xexpose.count == 0){
			redraw();
		}
		if(event.type == KeyPress && XLookupString(&event.xkey,text,255,&key,0) == 1) {
			if(text[0] == 'q') {
				close_x();
			}
			char c = text[0];
			std::string s = "you pressed the ";
			s += c;
			s += " key!\n";
			std::cout << s << std::endl;
		}
		if (event.type == ButtonPress) {
			std::cout << "you clicked at " + std::to_string(event.xbutton.x) + ", " + 
			std::to_string(event.xbutton.y) << std::endl;
			XSetForeground(dis, gc, black);
			XFillRectangle(dis, win, gc, event.xbutton.x - 5, event.xbutton.y - 5, 10, 10);
		}
	}
}

void get_colors() {
	XColor tmp;

	XParseColor(dis, DefaultColormap(dis, screen), "chartreuse", &tmp);
	XAllocColor(dis, DefaultColormap(dis, screen), &tmp);
	//chartreuse = tmp.pixel;
}

int main(int argc, char *argv[])
{
	std::cout << "Hello world! FECK FECK FECK" << std::endl;
	init_x();
	run_x();
}