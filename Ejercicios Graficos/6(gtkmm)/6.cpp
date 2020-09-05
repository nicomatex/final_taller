/*
> Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente imagen en su área de dibujo. (ES UN CIRCULO AZUL CENTRADO EN UNA PANTALLA BLANCA).
*/

#include <gtkmm.h>
#include <iostream>

#define RADIO 50

class Dibujo: public Gtk::DrawingArea{

	protected:
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
};

bool Dibujo::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){

	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	cr->set_source_rgb(1.0,1.0,1.0);
	cr->paint();

	cr->set_source_rgb(0.0,0.0,1.0);
	cr->arc(width/2,height/2,std::min(width/2,height/2),0,2.0 * M_PI);
	cr->fill_preserve();
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