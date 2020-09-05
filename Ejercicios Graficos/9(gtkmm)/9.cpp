/*
> Escriba una rutina de interfaz gráfica que cree una ventana que contenga el siguiente dibujo: (ES UN TRIANGULO ROJO CENTRADO EN UNA VENTANA BLANCA).
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
	cr->move_to(0,height);
	cr->line_to(width/2,0);
	cr->line_to(width,height);
	cr->line_to(0,height);
	cr->stroke_preserve();
	cr->fill();
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