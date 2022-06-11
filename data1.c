//#include <on_command.c>
long proc_main_wnd (HWND hwnd, UINT message, UINT wParam, long lParam)
{
char flnm[15] = "Database.txt";	
	switch(message)
	{
		case WM_CREATE:
		{
		FILE *hf;
		char str[50];
		HWND h=0;
		char *string;
		int k=0, i=0,x=0,y=0,w1=100,w2=200,h1=15,h2=25,d=2;
	
		CreateWindow("static","Name",WS_VISIBLE|WS_CHILD,x,y,w1,h1,
			hwnd,0,0,0);
		
		CreateWindow("edit","",WS_VISIBLE|WS_CHILD,x,y+h1+d,w2,h2,
			hwnd,(HMENU)1,0,0);

		CreateWindow("static","Surname",WS_VISIBLE|WS_CHILD,x,y+h1+h2+2*d,w1,h1,
			hwnd,0,0,0);

		CreateWindow("edit","",WS_VISIBLE|WS_CHILD,x,y+2*h1+h2+3*d,w2,h2,
			hwnd,(HMENU)2,0,0);

		CreateWindow("static","Age",WS_VISIBLE|WS_CHILD,x,y+2*h1+2*h2+4*d,w1,h1,
			hwnd,0,0,0);
		
		CreateWindow("edit","",WS_VISIBLE|WS_CHILD,x,y+3*h1+2*h2+5*d,w2,h2,
			hwnd,(HMENU)3,0,0);

		CreateWindow("button","Clear",WS_VISIBLE|WS_CHILD,x,y+3*h1+3*h2+6*d,w1,h2
			,hwnd,(HMENU)5,0,0);

		CreateWindow("button","Write in a file",WS_VISIBLE|WS_CHILD,x,y+3*h1+4*h2+7*d,w1,h2
			,hwnd,(HMENU)4,0,0);
		
		CreateWindow("button","Close",WS_VISIBLE|WS_CHILD,x,y+3*h1+5*h2+8*d,w1,h2
			,hwnd,(HMENU)30,0,0);
		
		CreateWindow("combobox","",WS_VISIBLE|WS_CHILD|WS_BORDER|CBS_SORT|WS_VSCROLL,w2,0,w2,400,
			hwnd,(HMENU)7,0,0);
		CreateWindow("combobox","SEARCH",WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL,w2+w2,0,w2,400,
			hwnd,(HMENU)8,0,0);

		if ((hf=fopen(&flnm,"r")) != NULL)
		{

		while (fgets(str, 500,hf) != NULL)
		{
		SendDlgItemMessage(hwnd,7,CB_ADDSTRING, 0,(long)str);			
		}		
		fclose(hf);
		}
	}
		break;

		case WM_COMMAND:

			switch(LOWORD(wParam))
			{
			case 8:
				if(HIWORD(wParam) == CBN_EDITCHANGE)
				{
				char str[50]="";
				int i=-1,k=0,t=1;
				int row[100]={-1};
				SendDlgItemMessage(hwnd,8,WM_GETTEXT, sizeof(str),(long)str);				
				SendDlgItemMessage(hwnd,8,CB_RESETCONTENT,0,0);
				SendDlgItemMessage(hwnd,8,WM_SETTEXT, strlen(str),(long)str);
				
					for(k=1;( row[k-1]-row[k-2]>0 );k++)
					{
					i= SendDlgItemMessage(hwnd,7,CB_FINDSTRING, i,(long)str);
					row[k]=i;
					}
					row[k-1]=-1;
					for(k=1;row[k]!= -1 ;k++)
					{
					SendDlgItemMessage(hwnd,7,CB_GETLBTEXT, row[k],(long)str);
					SendDlgItemMessage(hwnd,8,CB_INSERTSTRING,0,(long)str);
					}					
				}
			break;

			case 4:
				if(HIWORD(wParam) == BN_CLICKED)
				{
//					int t;
				FILE *hf;
				char str[256]="";
				int x;
				char str1[50]="";
				struct Person
				{
				char Name[20];
				char Surname[25];
				char age[4];
				}person;
				memset(&str,0,sizeof(str));
				memset(&str1,0,sizeof(str1));

					SendDlgItemMessage(hwnd,1,WM_GETTEXT,sizeof(str),(long) str);
					strcat(str1,str);
  					strcat(str1," ");
						if(strlen(&str)==0)
						{
						MessageBox(0,"Fill all of the fields",0,0);
						break;
						}
					memset(&str,0,sizeof(str));
					SendDlgItemMessage(hwnd,2,WM_GETTEXT,sizeof(str),(long) str);
					strcat(str1,str);
					strcat(str1," ");					
						if(strlen(str)==0)
						{
						MessageBox(0,"Fill all of the fields",0,0);
						break;
						}
					memset(&str,0,sizeof(str));
					SendDlgItemMessage(hwnd,3,WM_GETTEXT,sizeof(str),(long) str);
					strcat(str1,str);
					strcat(str1,"\n");
						if(strlen(str)==0)
						{
						MessageBox(0,"Fill all of the fields",0,0);
						break;
						}
					SendDlgItemMessage(hwnd,7,CB_ADDSTRING, 0,(long)str1);	

					hf=fopen(&flnm,"a+");
					fwrite(str1,strlen(str1),1,hf);			
					fclose(hf);			
				}
				break;

			case 5:
				if(HIWORD(wParam) == BN_CLICKED)
				{
					SendDlgItemMessage(hwnd,1,WM_SETTEXT,0,0);	//clearing edit boxes	
					SendDlgItemMessage(hwnd,2,WM_SETTEXT,0,0);		
					SendDlgItemMessage(hwnd,3,WM_SETTEXT,0,0);			
				}
			break;

			case 30:
				if(HIWORD(wParam) == BN_CLICKED)
//				exit(1);
				{
				DestroyWindow(1);
				exit(1);
				}
			break;
			}
		break;
	
//		WM_CLOSE
		default:
		break;
	}
return	DefWindowProc(hwnd,message,wParam,lParam);
}

