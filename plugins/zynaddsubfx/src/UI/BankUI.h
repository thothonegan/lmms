// generated by Fast Light User Interface Designer (fluid) version 1.0109

#ifndef BankUI_h
#define BankUI_h
#include <FL/Fl.H>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include "../Misc/Master.h"
#include "../Misc/Bank.h"
#include "../Misc/Config.h"

class BankProcess_ {
public:
  virtual void process();
  Bank *bank; 
};

class BankSlot : public Fl_Button,BankProcess_ {
public:
  BankSlot(int x,int y, int w, int h, const char *label=0);
  int handle(int event);
  void init(int nslot_, int *what_, int *whatslot_,void (BankProcess_:: *fnc_)(void),BankProcess_ *bp_,Bank *bank_,int *nselected_);
  void refresh();
private:
  int *what,*whatslot,nslot,highlight, *nselected; 
  void (BankProcess_:: *fnc)(void); 
  BankProcess_ *bp; 
};
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>

class BankUI : public BankProcess_ {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *bankuiwindow;
private:
  void cb_Close_i(Fl_Button*, void*);
  static void cb_Close(Fl_Button*, void*);
public:
  Fl_Group *modeselect;
  Fl_Light_Button *writebutton;
private:
  void cb_writebutton_i(Fl_Light_Button*, void*);
  static void cb_writebutton(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *readbutton;
private:
  void cb_readbutton_i(Fl_Light_Button*, void*);
  static void cb_readbutton(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *clearbutton;
private:
  void cb_clearbutton_i(Fl_Light_Button*, void*);
  static void cb_clearbutton(Fl_Light_Button*, void*);
public:
  Fl_Light_Button *swapbutton;
private:
  void cb_swapbutton_i(Fl_Light_Button*, void*);
  static void cb_swapbutton(Fl_Light_Button*, void*);
  void cb_New_i(Fl_Button*, void*);
  static void cb_New(Fl_Button*, void*);
  void cb_auto_i(Fl_Check_Button*, void*);
  static void cb_auto(Fl_Check_Button*, void*);
public:
  Fl_Choice *banklist;
private:
  void cb_banklist_i(Fl_Choice*, void*);
  static void cb_banklist(Fl_Choice*, void*);
  void cb_Refresh_i(Fl_Button*, void*);
  static void cb_Refresh(Fl_Button*, void*);
  void cb_Show_i(Fl_Check_Button*, void*);
  static void cb_Show(Fl_Check_Button*, void*);
public:
  BankUI(Master *master_,int *npart_);
  virtual ~BankUI();
  void show();
  void hide();
  void init(Fl_Valuator *cbwig_);
  void process();
  void refreshmainwindow();
  void removeselection();
  void rescan_for_banks();
  void simplesetmode(bool beginnerui);
private:
  BankSlot *bs[BANK_SIZE]; 
  int slot,what; //"what"=what button is pressed
  int mode,*npart,nselected; 
  Master *master; 
  void (BankProcess_::* fnc)(void); 
public:
  Fl_Valuator *cbwig; 
};
#endif