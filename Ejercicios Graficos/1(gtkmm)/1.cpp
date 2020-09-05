/*
> Escriba una rutina que dibuje las dos diagonales de la pantalla en color rojo.
*/

#include <gtkmm.h>
#include <iostream>

class Area : public Gtk::DrawingArea
{
	public:
		Area();
		~Area();
	protected:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

Area::Area(){}
Area::~Area(){}

bool Area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
	Gtk::Allocation allocation = get_allocation(); //Info de la ventana	
	const int height = allocation.get_height();
	const int width = allocation.get_width();

	cr->set_line_width(5.0);
	cr->set_source_rgb(1.0,0.0,0.0);
	cr->move_to(0,0);
	cr->line_to(width,height);
	cr->move_to(0,height);
	cr->line_to(width,0);
	cr->stroke();

	return true;
}

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Gtk::Window window;
	window.fullscreen();
	window.set_title("Ejercicio de dibujo");

	Area area;
	window.add(area);
	area.show();
	return app->run(window);
}
