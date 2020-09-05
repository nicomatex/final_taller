/*
> Escriba una rutina para ambiente gráfico que dibuje un rombo rojo, centrado que ocupe todo el espacio de la ventana.
*/

#include <gtkmm.h>
#include <iostream>


class Dibujo: public Gtk::DrawingArea{

	protected:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

bool Dibujo::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();


	cr->set_source_rgb(1.0,0.0,0.0);
	cr->move_to(0,height/2);
	cr->line_to(width/2,0);
	cr->line_to(width,height/2);
	cr->line_to(width/2,height);
	cr->line_to(0,height/2);
	cr->fill();
	cr->stroke();

	return true;
}

int main(int argc, char* argv[]){
	auto app = Gtk::Application::create(argc,argv,"ej.taller");

	Gtk::Window ventana;

	Dibujo dibujo;
	ventana.add(dibujo);
	dibujo.show();
	return app->run(ventana);
}