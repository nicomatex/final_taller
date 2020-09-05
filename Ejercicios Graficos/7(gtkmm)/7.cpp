/*
> Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente imagen en su área de dibujo. (ES UN CIRCULO AZUL CENTRADO EN UNA PANTALLA BLANCA).
*/

#include <gtkmm.h>
#include <iostream>

#define RADIO 50

void close_window(Glib::RefPtr<Gtk::Application>& app){
	app->quit();
}


int main(int argc, char* argv[]){
	auto app = Gtk::Application::create(argc,argv,"ej.taller");

	Gtk::Window ventana;
	
	Gtk::Button boton("Cerrar");
	ventana.add(boton);
	boton.show();

	boton.signal_clicked().connect(std::bind(sigc::ptr_fun(close_window),std::ref(app)));

	return app->run(ventana);
}