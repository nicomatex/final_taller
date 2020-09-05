/*
> Escriba una rutina de interfaz gráfica que  lance una aplicación de ventana simple, con un cuadro de texto y un botón. 
Al presionar el  botón, se debe borrar el valor ingresado por el usuario en el cuadro de texto.
*/

#include <gtkmm.h>
#include <iostream>

#define RADIO 50


void erase_content(Gtk::Entry& entry){
	entry.delete_text(0,entry.get_text_length());
}

int main(int argc, char* argv[]){
	auto app = Gtk::Application::create(argc,argv,"ej.taller");
	Gtk::Window ventana;
	
	Gtk::Box contenedor;
	ventana.add(contenedor);
	contenedor.show();

	Gtk::Entry text;
	contenedor.add(text);
	text.show();

	Gtk::Button boton("Borrar texto");
	contenedor.add(boton);
	boton.show();

	boton.signal_clicked().connect(std::bind(sigc::ptr_fun(erase_content),std::ref(text)));
	return app->run(ventana);
}