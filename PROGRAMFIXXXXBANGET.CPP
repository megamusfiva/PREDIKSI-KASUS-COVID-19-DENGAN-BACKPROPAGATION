#include <iostream.h>
#include <iomanip.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream.h>
#include <ctype.h>
#include <windows.h>
#include <cstring.h>
#include <strstrea.h>
#include <time.h>
void main ()
{
	ofstream JST;
	char file[50],nama[10],namafile[10];
	double data[200][10],target[200][10],dataa[200][10],targetawal[200][10];
   double datauji[200][10],targetuji[200][10],datau[200][10],targetujiawal[200][10];
	double v[200][10],aa[200],aaa[200],sigmak[200][10];
	double w0[200], w[200][10],b2[200], v0[200][10], vr[200][10],b1[200][10];
	double z_net[200][10], z[200][10], y_net[200][10], y[200][10];
   double sigmainj[200][10],delw[200],delwj[200][10],t_wjk[200][10];
	double r,MSE,alfa,MSEu,selisih[200][10],rata,rata2;
   double sgm[200][10],delv[200][10],deltav[200][10],datanormal[200][10];
	int pp,a,p,l,k,q,i,j,n,m,h,OUTPUT,jmlbbt,jmlbiash,jmly,biasy,iter, err,mm,xs;

	ifstream DataJST;
   ifstream DataJSTUji;
   ifstream TargetJST;
   ifstream TargetJSTUji;
		DataJST.open("Datalatih.txt");
      TargetJST.open ("targetlatih.txt");
      DataJSTUji.open("DataUji.txt");
   	TargetJSTUji.open("targetuji.txt");
      mm=79; //jumlah datauji
	   h=3; // jumlah hidden
   	n=3; //jumlah xi
  		m=187;  //jumlah data latih
   	jmlbbt=n*h;
   	jmlbiash=h;
   	jmly=1;
   	biasy=1;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			DataJST>>data[i][j];
		}
	}
	DataJST.close();
   for(i=0;i<m;i++)
	{
		for(j=0;j<jmly;j++)
		{
			TargetJST>>targetawal[i][j];
		}
	}
   TargetJST.close();

   for(i=0;i<mm;i++)
	{
		for(j=0;j<n;j++)
		{
			DataJSTUji>>datau[i][j];
		}
	}
	DataJSTUji.close();
	for(i=0;i<m;i++)
	{
		for(j=0;j<jmly;j++)
		{
			TargetJSTUji>>targetujiawal[i][j];
		}
	}
   TargetJSTUji.close();

   cout<<"\t     ====     UJIAN AKHIR SEMESTER MATA KULIAH JARINGAN SYARAF TIRUAN     ==== "<<endl;
	cout<<"\t =======                ARDIAN EKA, AFYDA IZZA, DAN MEGA M                 ======="<<endl;
	cout<<"\t     ====         PREDIKSI KASUS COVID-19 DENGAN BACKPROPAGATION          ==== "<<endl;
	cout<<"\t     =================================================================="<<endl<<endl;

	//INISIALISASI PARAMETER
	cout<<endl<<" INISIALISASI PARAMETER !"<<endl<<endl;
	do
	{
		cout<<" -> Learning Rate (0-1) : ";
		cin>>alfa;
		if(alfa<0||alfa>1)
		{
			cout<<"	Inputan salah, mohon ulangi! "<<endl;
		}
	}
	while(alfa<0||alfa>1);
	cout<<endl;
	do
	{
		cout<<" -> maks iterasi : ";
		cin>>iter;
		if(iter<0)
		{
			cout<<"	Inputan salah, mohon ulangi! "<<endl;
		}
	}
	while(iter<0);
	cout<<endl;

   cout<<"\n Penyimpanan output pada notepad : ";
	cout<<"\n   Nama file	: ";
	cin>>file;
	cout<<"	Nomer urut file : ";
	cin>>OUTPUT;
   //output notepad
	strcat(file," ke-");		//menambah karakter kedalam variabel
	strcpy(namafile,file);//maksudnya adalah mengcopy isi file ke namafile
	itoa(OUTPUT,nama,10);//misal diinputkan hasil=1234, membuat nama berisi 1234
	strcat(namafile,nama);//menambah karakter nama kedalam variabel namafile
	strcat(namafile,".txt");//strcat berfungsi untuk menggabungkan 2 buah string (melakukan penggabungan variabel namafile dan.txt)
   cout<<endl<<endl<<"\t\t -- DETAIL PERHITUNGAN DAPAT DILIHAT PADA FILE => "<<namafile<<" --"<<endl;
	JST.open(namafile);

	JST<<"\t     ====     UJIAN AKHIR SEMESTER MATA KULIAH JARINGAN SYARAF TIRUAN     ==== "<<endl;
	JST<<"\t =======                ARDIAN EKA, AFYDA IZZA, DAN MEGA M                 ======="<<endl;
	JST<<"\t     ====         PREDIKSI KASUS COVID-19 DENGAN BACKPROPOGATION          ==== "<<endl;
	JST<<"\t     =================================================================="<<endl<<endl;

	JST<<"\n => Pola Masukan Dan Target"<<endl;
   JST<<endl<<" - DATA PELATIHAN - "<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			JST<<data[i][j]<<"\t ";
		}
      for(j=0;j<jmly;j++)
		{
			JST<<targetawal[i][j]<<"\t ";
		}
   	JST<<endl;
	}
   JST<<endl<<" - DATA VALIDASI - "<<endl;
	for(i=0;i<mm;i++)
	{
		for(j=0;j<n;j++)
		{
			JST<<datau[i][j]<<"\t ";
		}
      for(j=0;j<jmly;j++)
		{
			JST<<targetujiawal[i][j]<<"\t ";
		}
   	JST<<endl;
	}
	//NORMALISASI
	JST<<"\n => NORMALISASI DATA "<<endl<<endl;
	JST<<"\t - NILAI MAXIMUM DAN MINIMUM - "<<endl;
	double max,min;
   min=0;max=8369;
   JST<<"MAX : "<<"\t "<<max<<endl;
   JST<<"MIN : "<<"\t "<<min<<endl;
   JST<<endl;
	//TABEL NORMAL
	JST<<"\t - TABEL SETELAH NORMALISASI - "<<endl;
   JST<<" -- DATA PELATIHAN -- "<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			dataa[i][j]=0.8*((data[i][j]-min)/(max-min))+0.1;
      	JST<<setprecision(3)<<dataa[i][j]<<"\t ";
   	}
      for(j=0;j<jmly;j++)
		{
			target[i][j]=0.8*((targetawal[i][j]-min)/(max-min))+0.1;
      	JST<<setprecision(3)<<target[i][j]<<"\t ";
   	}
    	JST<<endl;
	}
   JST<<endl<<" -- DATA VALIDASI -- "<<endl;
	for(i=0;i<mm;i++)
	{
		for(j=0;j<n;j++)
		{
			datauji[i][j]=0.8*((datau[i][j]-min)/(max-min))+0.1;
         targetuji[i][j]=datauji[i][n+1];
      	JST<<setprecision(3)<<datauji[i][j]<<"\t ";
   	}
      for(j=0;j<jmly;j++)
		{
			targetuji[i][j]=0.8*((targetujiawal[i][j]-min)/(max-min))+0.1;
      	JST<<setprecision(3)<<targetuji[i][j]<<"\t ";
   	}
    	JST<<endl;
	}
 	JST<<endl<<"======================================================================================================================"<<endl;

	//MULAI PELATIHAN
	JST<<endl<<"\t\t Proses Pelatihan menggunakan Algoritma Backpropagation"<<endl;
	//INISIALISASI BOBOT DAN BIAS RANDOM
	randomize();
	JST<<endl<<"Bobot dan Bias Input Layer ke Hidden Layer <acak>"<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<h;j++)
		{
			r=random(1000);
      	vr[i][j]=r*0.0001;
      	JST<<vr[i][j]<<"\t ";
      	v[i][j]=vr[i][j];
		}
   	JST<<endl;
	}
	for(i=0;i<1;i++)
	{
   	for(j=0;j<h;j++)
		{
   		r=random(1000);
   		b1[i][j]=r*0.0001;
   		JST<<b1[i][j]<<"\t ";
   		v0[i][j]=b1[i][j];
      }
	}
	JST<<endl;
	JST<<endl<<"Bobot dan Bias Hidden Layer ke Output Layer <acak>"<<endl;
	for(i=0;i<h;i++)
	{
		for(j=0;j<jmly;j++)
		{
			r=random(1000);
      	w[i][j]=r*0.0001;
      	JST<<w[i][j]<<"\t ";
		}
   	JST<<endl;
	}
	for(i=0;i<jmly;i++)
	{
   	r=random(1000);
   	b2[i]=r*0.0001;
   	JST<<b2[i]<<"\t ";
   	w0[i]=b2[i];
	}
	JST<<endl;
	JST<<endl<<"*********************************************************************"<<endl<<endl;
	for(pp=1;pp<=iter;pp++)
	{
   	JST<<"\t >> PROSES FEEDFORWARD <<"<<endl<<endl;
   	JST<<">> Iterasi ke- "<<pp<<endl<<endl;
   	for(k=0;k<h;k++)
		{
			for(l=0;l<jmly;l++)
			{
				t_wjk[l][k]=w[k][l];
			}
		}
		for(a=0;a<m;a++)  //polanya
		{
			//JST<<endl<<" Elemen z_net :"<<endl;
   		for(l=0;l<h;l++)   //hiddennya
   		{
      		//JST<<"v0[a] :"<<v0[0][l]<<endl;
         	z_net[a][l]=v0[0][l];
	   		for(k=0;k<n;k++)   //xnya
   			{
   				//JST<<"data[a][k] : "<<dataa[a][k]<<endl;
      			//JST<<"v[k][l] :"<<v[k][l]<<endl;
		  			z_net[a][l]=z_net[a][l]+dataa[a][k]*v[k][l];
      		}
      		//JST<<" z_net("<<l+1<<") "<<setprecision(5)<<z_net[a][l]<<endl;
   		}
	   	//JST<<endl<<" Elemen z :"<<endl;
  			for(l=0;l<h;l++)
 			{
      		aa[l]=1+exp(-1*z_net[a][l]);
   			z[a][l]=1/aa[l];
      		//JST<<" z("<<l+1<<") "<<setprecision(5)<<z[a][l]<<endl;
   		}
		}
		JST<<"z_net1"<<"\t "<<"z_net2"<<"\t "<<"z_net3"<<"\t "<<"z1"<<"\t "<<"z2"<<"\t "<<"z3"<<endl;
		for(a=0;a<m;a++)  //polanya
		{
			for(l=0;l<h;l++)
	   	{
   			JST<<setprecision(3)<<z_net[a][l]<<"\t ";
   		}
   		for(l=0;l<h;l++)
   		{
   			JST<<setprecision(3)<<z[a][l]<<"\t ";
      	}
   		JST<<endl;
		}
  		//Y NET DAN Y
   	for(a=0;a<m;a++)  //polanya
		{
   		//JST<<endl<<" Elemen y_net dan y :"<<endl;
  			for(l=0;l<jmly;l++)   //y nya
   		{
      		//JST<<"w0[l] : "<<w0[l]<<endl;
      		y_net[a][l]=w0[l];
   			for(k=0;k<h;k++)   //hiddennya
   			{
      			//JST<<"w[a][l] : "<<w[k][l]<<endl;
      			//JST<<"z[a][k] : "<<z[a][k]<<endl;
         		y_net[a][l]=y_net[a][l]+z[a][k]*w[k][l];
      		}
    			//JST<<" y_net("<<l+1<<") "<<setprecision(5)<<y_net[a][l]<<endl;
   		}
  			for(l=0;l<jmly;l++)
 			{
   			aaa[l]=1+exp(-1*y_net[a][l]);
				y[a][l]=1/aaa[l];
      		//JST<<" y("<<l+1<<") "<<setprecision(5)<<y[a][l]<<endl;
  			}
   		//JST<<endl;
		}
		JST<<endl;
		JST<<"y_net1"<<"\t "<<" y1"<<endl;
		for(a=0;a<m;a++)
		{
			for(l=0;l<jmly;l++)
   		{
   			JST<<setprecision(4)<<y_net[a][l]<<"\t ";
   		}
   		for(l=0;l<jmly;l++)
   		{
   			JST<<setprecision(4)<<y[a][l]<<"\t\t ";
   		}
   		JST<<endl;
		}
      JST<<endl;
      JST<<"PERHITUNGAN ERROR MSE iterasi ke-"<<pp<<" : "<<endl;
      MSE=0;
   	for(a=0;a<m;a++)
		{
			for(l=0;l<jmly;l++)
   		{
				MSE=MSE+(pow((target[a][l]-y[a][l]),2))/m;
			}

   	}
      JST<<" MSE "<<" : "<<MSE<<endl;
   	//PEMBARUAN BOBOT && BIAS
      JST<<endl<<"*********************************************************************"<<endl<<endl;
      JST<<"\t >> PERBARUAN BOBOT && BIAS PADA JARINGAN << "<<endl;
   	//JST<<"Matrik sigmak="<<endl;
   	for(a=0;a<m;a++)
		{
			for(l=0;l<jmly;l++)
   		{
				sigmak[a][l]=(target[a][l]-y[a][l])*(1-y[a][l])*y[a][l];
         	//JST<<sigmak[a][l]<<"         ";
      	}
      	//JST<<endl;
		}
      //JST<<endl;
     	//JST<<"Matrik delta_w0k="<<endl;
   	for(a=0;a<m;a++)  //polanya
		{
  			for(l=0;l<jmly;l++)   //y nya
   		{
				delw[a]=alfa*sigmak[a][l];
         	//JST<<delw[a]<<"         ";
      	}
      	//JST<<endl;
		}
      //JST<<endl;
      //JST<<"Matrik delta_wjk="<<endl;
   	for(a=0;a<m;a++)  //polanya
		{
  			for(l=0;l<jmly;l++)   //y nya
   		{
         	for(k=0;k<h;k++)   //hiddennya
   			{
					delwj[a][k]=alfa*sigmak[a][l]*z[a][k];
         		//JST<<delwj[a][k]<<"         ";
            }
      	}
      	//JST<<endl;
		}
      //JST<<endl;
      xs=jmly*h;
      //JST<<"Matrik sigma inj="<<endl;
      for(a=0;a<m;a++)  //polanya
      {
         for(l=0;l<jmly;l++)   //y nya
      	{
            for(k=0;k<h;k++)   //hiddennya
				{
            	sigmainj[a][k]=sigmak[a][l]*t_wjk[l][k];
               //JST<<setprecision(5)<<sigmainj[a][k]<<"         ";
            }
            //JST<<endl;
			}
		}
      //JST<<endl;
      //JST<<"Matrik sigmaj="<<endl;
      for(i=0;i<m;i++)  //polanya
      {
         for(j=0;j<h;j++)   //hiddennya
			{
				sgm[i][j]=sigmainj[i][j]*z[i][j];
            //JST<<sgm[i][j]<<"         ";
         }
         //JST<<endl;
		}
      //JST<<endl;
      //JST<<"Matrik delta_v0k="<<endl;
   	for(a=0;a<m;a++)  //polanya
		{
  			for(l=0;l<h;l++)   //x nya
   		{
				delv[a][l]=alfa*sgm[a][l];
         	//JST<<delv[a][l]<<"         ";
      	}
      	//JST<<endl;
		}
      //JST<<endl;
      //JST<<"Matrik delta_vjk="<<endl;
   	for(a=0;a<m;a++)  //polanya
		{
  			for(l=0;l<h;l++)   //hidden nya
   		{
         	for(k=0;k<n;k++)   //inputnya
   			{  //JST<<sgm[a][l]<<" x  "<<dataa[a][k]<<endl;
					deltav[a][k]=alfa*sgm[a][l]*dataa[a][k];
         		//JST<<deltav[a][k]<<"         ";
            }
      	}
      	//JST<<endl;
		}
      //JST<<endl;
   	//JST<<"\n Bias optimal W0k = "<<endl;
      for(l=0;l<jmly;l++)   //y nya
      {
      	for(a=0;a<m;a++)  //polanya
			{
      		w0[a]=w0[l];
      		w0[a]=w0[a]+delw[a];
            if(w0[a]<0 || w0[a]>1)
            {
					w0[a]=1/(1+exp(-1*w0[a]));
            }
            w0[l]=w0[a];
            //JST<<w0[a]<<endl;
         }
         //JST<<endl;
		}
      //JST<<"Bobot optimal Wjk = "<<endl;
      for(a=0;a<m;a++)  //polanya
      {
         for(l=0;l<jmly;l++)   //y nya
      	{
            for(k=0;k<h;k++)   //hiddennya
				{
               w[l][k]=w[k][l];
               w[l][k]=w[l][k]+delwj[a][k];
               if(w[l][k]<0 || w[l][k]>1)
            	{
						w[l][k]=1/(1+exp(-1*w[l][k]));
            	}
               w[k][l]=w[l][k];
            	//JST<<setprecision(3)<<w[l][k]<<"  ";
            }
            //JST<<endl;
         }
		}
      //JST<<endl;
      //JST<<"Bias optimal V0k = "<<endl;
      for(a=0;a<m;a++)  //polanya
      {
      	for(l=0;l<h;l++)   //hiddennya nya
      	{
         	v0[a][l]=v0[0][l];
      		v0[a][l]=v0[a][l]+delv[a][l];
             if(v0[a][l]<0 || v0[a][l]>1)
            	{
						v0[a][l]=1/(1+exp(-1*v0[a][l]));
            	}
            v0[0][l]=v0[a][l];
            //JST<<setprecision(3)<<v0[a][l]<<"  ";
         }
         //JST<<endl;
		}
      //JST<<endl;
      //JST<<"Bobot optimal Vjk = "<<endl;
      for(a=0;a<m;a++)  //polanya
      {
         for(l=0;l<h;l++)   //hidden nya
      	{
            for(k=0;k<n;k++)   //inputnya
				{
               v[k][l]=v[k][l];
               v[k][l]=v[k][l]+deltav[a][k];
               if(v[k][l]<0 || v[k][l]>1)
            	{
						v[k][l]=1/(1+exp(-1*v[k][l]));
            	}
            	//JST<<setprecision(3)<<v[k][l]<<"  ";
            }
         }
         //JST<<endl;
		}
      JST<<endl<<"Bobot dan Bias Input Layer ke Hidden Layer"<<endl;
		for(i=0;i<n;i++)
		{
			for(j=0;j<h;j++)
			{
      		v[i][j]=v[i][j];
            JST<<setprecision(3)<<v[i][j]<<"\t    ";
			}
   		JST<<endl;
		}
		for(i=0;i<1;i++)
		{
   		for(j=0;j<h;j++)
			{
   			v0[i][j]=v0[i][j];
            JST<<setprecision(3)<<v0[i][j]<<"\t    ";
      	}
		}
		JST<<endl;
		JST<<endl<<"Bobot dan Bias Hidden Layer ke Output Layer"<<endl;
		for(i=0;i<h;i++)
		{
			for(j=0;j<jmly;j++)
			{
            w[i][j]=w[i][j];
      		JST<<setprecision(3)<<w[i][j]<<"\t ";
			}
   		JST<<endl;
		}
		for(i=0;i<jmly;i++)
		{
   		w0[i]=w0[i];
         JST<<setprecision(3)<<w0[i]<<"\t ";
		}
		JST<<endl;
      JST<<endl<<"*********************************************************************"<<endl;
	}
   JST<<"======================================================================================================================"<<endl<<endl;
   JST<<"\t\t >> PREDIKSI MENGGUNAKAN DATA VALIDASI <<"<<endl<<endl;
   for(a=0;a<mm;a++)  //polanya
  	{
 		//JST<<endl<<" Elemen z_net :"<<endl;
      for(l=0;l<h;l++)   //hiddennya
     	{
     		//JST<<"v0[a] :"<<v0[0][l]<<endl;
        	z_net[a][l]=v0[0][l];
     		for(k=0;k<n;k++)   //xnya
  			{
         	//JST<<"datauji[a][k] : "<<datauji[a][k]<<endl;
      	  	//JST<<"v[k][l] :"<<v[k][l]<<endl;
		  	 	z_net[a][l]=z_net[a][l]+datauji[a][k]*v[k][l];
      	}
        //JST<<" z_net("<<l+1<<") "<<setprecision(5)<<z_net[a][l]<<endl;
   	 }
	   //JST<<endl<<" Elemen z :"<<endl;
  	  	for(l=0;l<h;l++)
 	 	{
     		aa[l]=1+exp(-1*z_net[a][l]);
     		z[a][l]=1/aa[l];
     		//JST<<" z("<<l+1<<") "<<setprecision(5)<<z[a][l]<<endl;
   	}
  	}
   JST<<"z_net1"<<setw(12)<<"z_net2"<<setw(12)<<"z_net3"<<setw(12)<<"z1"<<setw(12)<<"z2"<<setw(12)<<"z3"<<endl;
  	for(a=0;a<mm;a++)  //polanya
   {
  		for(l=0;l<h;l++)
      {
     		JST<<setprecision(3)<<z_net[a][l]<<setw(12);
    	}
      for(l=0;l<h;l++)
     	{
    		JST<<setprecision(3)<<z[a][l]<<setw(12);
      }
     	JST<<endl;
	 }
  	//Y NET DAN Y
  	for(a=0;a<mm;a++)  //polanya
 	{
  		//JST<<endl<<" Elemen y_net dan y :"<<endl;
  		for(l=0;l<jmly;l++)   //y nya
     	{
     		//JST<<"w0[l] : "<<w0[l]<<endl;
       	y_net[a][l]=w0[l];
   		for(k=0;k<h;k++)   //hiddennya
     		{
     			//JST<<"w[a][l] : "<<w[k][l]<<endl;
      	  	//JST<<"z[a][k] : "<<z[a][k]<<endl;
          	y_net[a][l]=y_net[a][l]+z[a][k]*w[k][l];
      	}
    	  	//JST<<" y_net("<<l+1<<") "<<setprecision(5)<<y_net[a][l]<<endl;
   	 }
  		for(l=0;l<jmly;l++)
 	  	{
    		aaa[l]=1+exp(-1*y_net[a][l]);
  			y[a][l]=1/aaa[l];
     		//JST<<" y("<<l+1<<") "<<setprecision(5)<<y[a][l]<<endl;
      }
     	//JST<<endl;
   }
   JST<<endl;
   JST<<"y_net1"<<setw(15)<<" y1"<<endl;
   for(a=0;a<mm;a++)
   {
	   for(l=0;l<jmly;l++)
   	{
      	JST<<setprecision(5)<<y_net[a][l]<<setw(15);
      }
      for(l=0;l<jmly;l++)
     	{
    		JST<<setprecision(5)<<y[a][l]<<setw(15);
   	}
  		JST<<endl;
  	}
    JST<<endl;
      JST<<"MSE VALIDASI : "<<endl;
      MSEu=0;
   	for(a=0;a<mm;a++)
		{
			for(l=0;l<jmly;l++)
   		{  //JST<<y[a][l]<<endl;
				MSEu=MSEu+(pow((targetuji[a][l]-y[a][l]),2))/mm;
			}

   	}
      JST<<" MSE UJI "<<" : "<<MSEu<<endl;
   JST<<endl<<"======================================================================================================================"<<endl<<endl;
	JST<<"\t\t >> DENORMALISASI DATA << "<<endl;
   JST<<"\n => DATA HASIL PREDIKSI "<<endl;
	for(i=0;i<mm;i++)
	{
		for(j=0;j<jmly;j++)
		{
         //JST<<y[i][j]<<endl;
			datanormal[i][j]=(((y[i][j]-0.1)*(max-min))/0.8)+min;
      	JST<<y[i][j]<<" -> "<<datanormal[i][j]<<"\t\t ";
   	}
    	JST<<endl;
	}
   JST<<"\n => ERROR PREDIKSI : "<<endl;
   rata=0;
   selisih[i][j]=0;
   for(i=0;i<mm;i++)
	{
		for(j=0;j<jmly;j++)
		{
			selisih[i][j]=(abs(datanormal[i][j]-targetujiawal[i][j]))/targetujiawal[i][j];
         rata=rata+selisih[i][j];
   	}
      rata2=rata/mm;
	}
   JST<<"Error :"<<rata2<<endl;
   JST<<endl<<"======================================================================================================================"<<endl;
   cout<<endl<<"======================================================================================================================"<<endl;
   char va;
   int mmm,mmmm,minn,maxx;
   double  dataum[100][10],datamanual[100][5],targetmanual[100][3],dataamanual[100][5],targettmanual[100][3] ;
   double  datanormall[100][100],selisihh[100][100];
   cout<<endl<<"Lanjut Peramalan dengan data baru [Y/T] ? ";
   cin>>va;
   cout<<endl;
   if(va=='Y'||va=='y')
   {
   	do
		{
      	ulang:
			cout<<"Masukkan banyaknya data (min 4 data): ";
			cin>>mmm;
			if(mmm<4)
			{
				cout<<"	Inputan salah, mohon ulangi! "<<endl;
            goto ulang;
			}
		}
		while(mmm<4);
      cout<<endl;
      n=3;
      for(i=0;i<mmm;i++)
      {
        	cout<<"Data ke-"<<i+1<<" : ";
      	cin>>dataum[i][0];
      }
      mmmm=mmm-3;
      cout<<endl;
      cout<<"Pola Data : "<<endl;
      for(i=0;i<mmmm;i++)
      {
      	for(j=0;j<n;j++)
      	{
            datamanual[i][0]= dataum[i][0];
            datamanual[i][1]= dataum[i+1][0];
            datamanual[i][2]= dataum[i+2][0];
            targetmanual[i][3]=dataum[i+3][0];
            cout<<datamanual[i][j]<<"       ";
         }
         cout<<targetmanual[i][3]<<"       ";
         cout<<endl;
      }
      cout<<endl;

		cout<<"\t - NORMALISASI - "<<endl;
      minn=1000000;maxx=0;
		for(i=0;i<mmm;i++)
		{
  			if(minn>dataum[i][0])
     	 	{ 		minn=dataum[i][0];}
		}
		for(i=0;i<mmm;i++)
		{
	  		if(maxx<dataum[i][0])
  			{		maxx=dataum[i][0];}
		}
		for(i=0;i<mmmm;i++)
		{
			for(j=0;j<n;j++)
			{
				dataamanual[i][j]=0.8*((datamanual[i][j]-minn)/(maxx-minn))+0.1;
     	 		cout<<setprecision(3)<<dataamanual[i][j]<<"\t ";
   		}
         targettmanual[i][3]=0.8*((targetmanual[i][3]-minn)/(maxx-minn))+0.1;
         cout<<setprecision(3)<<targettmanual[i][3]<<"\t ";
    		cout<<endl;
		}
      cout<<endl<<"*********************************************************************"<<endl;
      cout<<endl<<"\t >> PROSES FEEDFORWARD << "<<endl;
      cout<<endl<<"Bobot dan Bias Input Layer ke Hidden Layer"<<endl;
		for(i=0;i<n;i++)
		{
			for(j=0;j<h;j++)
			{
      		v[i][j]=v[i][j];
            cout<<setprecision(3)<<v[i][j]<<"\t    ";
			}
   		cout<<endl;
		}
		for(i=0;i<1;i++)
		{
   		for(j=0;j<h;j++)
			{
   			v0[i][j]=v0[i][j];
            cout<<setprecision(3)<<v0[i][j]<<"\t    ";
      	}
		}
		cout<<endl;
		cout<<endl<<"Bobot dan Bias Hidden Layer ke Output Layer"<<endl;
		for(i=0;i<h;i++)
		{
			for(j=0;j<jmly;j++)
			{
            w[i][j]=w[i][j];
      		cout<<setprecision(3)<<w[i][j]<<"\t ";
			}
   		cout<<endl;
		}
		for(i=0;i<jmly;i++)
		{
   		w0[i]=w0[i];
         cout<<setprecision(3)<<w0[i]<<"\t ";
		}
		cout<<endl<<endl;

      for(a=0;a<mmmm;a++)  //polanya
  		{
      	for(l=0;l<h;l++)   //hiddennya
     		{
        		z_net[a][l]=v0[0][l];
     			for(k=0;k<n;k++)   //xnya
  				{
		  	 		z_net[a][l]=z_net[a][l]+dataamanual[a][k]*v[k][l];
      		}
      	}
  	  		for(l=0;l<h;l++)
 	 		{
     			aa[l]=1+exp(-1*z_net[a][l]);
     			z[a][l]=1/aa[l];
     	  	}
  		}
		cout<<"z_net1"<<setw(15)<<"z_net2"<<setw(15)<<"z_net3"<<setw(15)<<"z1"<<setw(15)<<"z2"<<setw(15)<<"z3"<<endl;
  		for(a=0;a<mmmm;a++)  //polanya
   	{
  			for(l=0;l<h;l++)
      	{
     			cout<<setprecision(3)<<z_net[a][l]<<setw(15);
    		}
      	for(l=0;l<h;l++)
     		{
    			cout<<setprecision(3)<<z[a][l]<<setw(15);
      	}
     		cout<<endl;
	 	}
  		//Y NET DAN Y
  		for(a=0;a<mmmm;a++)  //polanya
 		{
  			for(l=0;l<jmly;l++)   //y nya
     		{
       		y_net[a][l]=w0[l];
   			for(k=0;k<h;k++)   //hiddennya
     			{
          		y_net[a][l]=y_net[a][l]+z[a][k]*w[k][l];
      		}
   	 	}
  			for(l=0;l<jmly;l++)
 	  		{
    			aaa[l]=1+exp(-1*y_net[a][l]);
  				y[a][l]=1/aaa[l];
      	}
   	}
   	cout<<endl;
   	cout<<"y_net1"<<setw(15)<<" y1"<<endl;
   	for(a=0;a<mmmm;a++)
   	{
	   	for(l=0;l<jmly;l++)
   		{
      		cout<<setprecision(5)<<y_net[a][l]<<setw(15);
      	}
      	for(l=0;l<jmly;l++)
     		{
    			cout<<setprecision(5)<<y[a][l]<<setw(15);
   		}
  			cout<<endl;
  		}
    	cout<<endl;
      cout<<"\n => MSE VALIDASI : "<<endl;
      MSEu=0;
   	for(a=0;a<mmmm;a++)
		{
			for(l=0;l<jmly;l++)
   		{  //JST<<y[a][l]<<endl;
				MSEu=MSEu+(pow((targettmanual[a][l]-y[a][l]),2))/mmmm;
			}
   	}
      cout<<"MSE UJI "<<" : "<<MSEu<<endl<<endl;
      cout<<"*********************************************************************"<<endl;
      cout<<"\t >> DENORMALISASI DATA << "<<endl;
		for(i=0;i<mmmm;i++)
		{
			for(j=0;j<jmly;j++)
			{
         	//JST<<y[i][j]<<endl;
				datanormall[i][j]=(((y[i][j]-0.1)*(max-min))/0.8)+min;
      		cout<<y[i][j]<<" -> "<<datanormall[i][j]<<"\t\t ";
   		}
    		cout<<endl;
		}
   	cout<<"\n => ERROR PREDIKSI : "<<endl;
   	rata=0;
   	selisihh[i][j]=0;
   	for(i=0;i<mmmm;i++)
		{
			for(j=0;j<jmly;j++)
			{
				selisihh[i][j]=(abs(datanormall[i][j]-targetmanual[i][3]))/targetmanual[i][3];
         	rata=rata+selisihh[i][j];
   		}
      	rata2=rata/mmmm;
		}
   	cout<<"Error :"<<rata2<<endl;
   }
   else if (va=='T'||va=='t')
   { exit(0); }
	cout<<endl;
   
getch();
}
