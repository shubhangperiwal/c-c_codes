#include<gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<math.h>
#include<crypt.h>

struct register_t {
	int functionality;
	char username[50];
	char password[50];};


char a[50], s[50];
static void button_clicked(GtkWidget** entry, GtkWidget* widget)
{
	GtkWidget *entry_ptr_a,*entry_ptr_s,*window; 
	entry_ptr_a = entry[0];
  	entry_ptr_s = entry[1];
	window = entry[3];
	//g_print("%s",gtk_entry_get_text(GTK_ENTRY(entry_ptr_a)));
	strcpy(a,gtk_entry_get_text(GTK_ENTRY(entry_ptr_a)));
    	strcpy(s,gtk_entry_get_text(GTK_ENTRY(entry_ptr_s)));
	gtk_widget_destroy (widget);
}

int main(int argc,char* argv[])
{
	static GtkWidget *entry[3];
	gtk_init(&argc,&argv);
	GtkWidget *window,*label1,*label2,*entry1,*entry2,*button,*table;
	
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

	table=gtk_table_new(10,10,0);
	label1=gtk_label_new("Hello tHere");
	entry1=gtk_entry_new();
	gtk_label_set_text(GTK_LABEL(label1),"Enter username");
	gtk_table_attach(GTK_TABLE(table),label1,0,1,1,2,GTK_FILL,GTK_FILL,0,0);
	gtk_table_attach(GTK_TABLE(table),entry1,2,3,1,2,GTK_FILL,GTK_FILL,0,0);
	gtk_table_set_row_spacings (GTK_TABLE(table),10);
	gtk_table_set_col_spacings (GTK_TABLE(table),5);

	label2=gtk_label_new("Enter Password");
	entry2=gtk_entry_new();
	entry[0] = entry1;
	entry[1] = entry2;
	entry[2] = window;
	gtk_table_attach(GTK_TABLE(table),label2,0,1,5,6,GTK_FILL,GTK_FILL,0,0);
	gtk_table_attach(GTK_TABLE(table),entry2,2,3,5,6,GTK_FILL,GTK_FILL,0,0);
	gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
	button=gtk_button_new_with_mnemonic("Confirm");
	gtk_table_attach(GTK_TABLE(table),button,1,2,6,7,GTK_FILL,GTK_FILL,0,0);
	
	gtk_table_set_row_spacings (GTK_TABLE(table),5);
	gtk_table_set_col_spacings (GTK_TABLE(table),5);
	g_signal_connect_swapped(button,"clicked",G_CALLBACK(button_clicked),entry);


	//gtk_container_add(GTK_CONTAINER(window),label);
	gtk_container_add(GTK_CONTAINER(window),table);
	gtk_widget_set_size_request(window,400,200);
	gtk_window_set_title(GTK_WINDOW(window),"REGISTER USER");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);



	gtk_widget_show_all(window);
	gtk_main();

	int num;
	printf("%s\n",a);
	printf("%s\n",s);

	
//Passing all values to the server
	int csd,cnewsd;
	struct register_t rgs;
	strcpy(rgs.username,a);
	strcpy(rgs.password,crypt(s,"aa"));
	rgs.functionality=1;
	struct sockaddr_in csadd,ccadd;

	csd=socket(AF_INET,SOCK_STREAM,0);
	csadd.sin_family=AF_INET;
	csadd.sin_addr.s_addr=inet_addr("127.0.0.1");
	csadd.sin_port=htons(10200);

	int result=connect(csd,(struct sockaddr*)&csadd,sizeof(csadd));
	if(result==-1)
		perror("Fuck Me Again");
	int m=write(csd,(struct register_t*)&rgs,sizeof(struct register_t));

		
	return 0;
}
