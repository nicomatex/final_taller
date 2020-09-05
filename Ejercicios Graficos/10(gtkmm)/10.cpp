/*
> Escriba una función que cargue un listbox (combo o dropdown) con 10 strings de la forma "opción xx", siendo xx una cadena de 2 dígitos con la forma 01,02,...10.
*/

#include <gtkmm.h>
#include <iostream>
#include <iomanip>

Gtk::ComboBoxText* create_listbox(){

	auto combo = new Gtk::ComboBoxText;
	
	for(size_t i = 1;i <= 10;i++){
		char str[10];
		std::sprintf(str,"opcion %02ld",i);
		combo->append(str);	
	}
	return combo;
}

int main(int argc, char* argv[]){
	auto app = Gtk::Application::create(argc,argv,"ej.taller");
	Gtk::Window ventana;

	Gtk::ComboBoxText* combo = create_listbox();
	ventana.add(*combo);
	combo->show();

	return app->run(ventana);
}