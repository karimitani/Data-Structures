struct URLRecord {
  char * _url;          
  char * _description;  
};

struct URLRecordList {
  URLRecord * _urlRecord;  
  URLRecordList * _next;   
};