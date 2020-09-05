/*
> Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un círculo verde del tamaño de la ventana.
*/

#include <gtkmm.h>
#include <iostream>

class Area : public Gtk::DrawingArea
{
	protected:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};


bool Area::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
	Gtk::Allocation allocation = get_allocation(); //Info de la ventana
	const int height = allocation.get_height();
	const int width = allocation.get_width();

	cr->set_line_width(5.0);
	cr->set_source_rgb(0.0,1.0,0.0);

	cr->arc(width/2,height/2,std::min(width/2,height/2) / 2,0.0,2.0 * M_PI);
	cr->stroke();

	cr->arc(width/2,height/2,std::min(width/2,height/2) / 4,0.0,2.0 * M_PI);
	cr->stroke();

	cr->arc(width/2,height/2,std::min(width/2,height/2) / 6,0.0,2.0 * M_PI);
	cr->stroke();

	return true;
}

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Gtk::Window window;
	window.set_default_size(600,480);
	window.set_title("Ejercicio de dibujo");

	Area area;
	window.add(area);
	area.show();
	return app->run(window);
}

