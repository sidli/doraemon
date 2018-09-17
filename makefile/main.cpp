    cout<<sizeof(Parent)<<"    "<<sizeof(Child)<<endl;
    Parent* p = new Child;
    string* pc = &(static_cast<Child*>(p)->str);
    cout<<sizeof(string)<<"     "<<sizeof(int)<<endl;
    cout<<&(*p)<<"      "<<&(p->i)<<"   "<<pc<<"        ";
delete p;
    cout<<*pc<<endl;
    return 0;

16    24
8	4
0xf1d3010	0xf1d3018	0xf1d3020	


16    24
8	4
0xc450010	0xc450018