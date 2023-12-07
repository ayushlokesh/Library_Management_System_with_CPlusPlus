#include "library.h"
#include <memory>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

//==============================================================================

// Default Constructor
Document::Document() { }

//Modified constructor
Document::Document(const char* title, int qty) : _title(std::string(title)), _quantity{qty} { }

// Copy Constructor
Document::Document(const Document& doc) : _title(doc._title){
  // _title = new char[strlen(doc._title) + 1];
  // strcpy(_title, doc._title);
  _quantity = doc._quantity;
}

// Copy Assignment Operator
Document& Document::operator=(const Document& doc) {
  // delete[] _title;
  // _title = new char[strlen(doc._title) + 1];
  // strcpy(_title, doc._title);
  _quantity = doc._quantity;
  return *this;
}

// Move Constructor
Document::Document(Document&& doc) : _title(doc._title){
  // _title = doc._title;
  _quantity = doc._quantity;
  // doc._title = NULL;
}

// Move Assignment Operator
Document& Document::operator=(Document&& doc) {
  // delete[] _title;
  // _title = doc._title;
  _quantity = doc._quantity;
  // doc._title = NULL;
  return *this;
}

Document::~Document() { }

void Document::updateTitle(const char *newTitle) {
  // delete[] _title;
  // _title = new char[strlen(newTitle) + 1];
  // strcpy(_title, newTitle);
  _title = std::string(newTitle);
}
void Document::updateQuantity(int newQuantity) { _quantity = newQuantity; }

const char *Document::getTitle() { return _title.c_str(); }
int Document::getQuantity() { return _quantity; }

bool Document::borrowDoc() {
  if (_quantity > 0) {
    _quantity--;
    return 1;
  }
  return 0;
}

void Document::returnDoc() { _quantity++; }

//==============================================================================

Novel::Novel(const char *title, const char *author, int quantity) : Document(title, quantity), _author(author){
  // _title = new char[strlen(title) + 1];
  // _author = new char[strlen(author) + 1];
  // strcpy(_title, title);
  // strcpy(_author, author);
  _quantity = quantity;
}

// Explicit Copy Constructor
Novel::Novel(const Novel& n) : Document(n), _author(n._author){
  // _title = new char[strlen(n._title) + 1];
  // _author = new char[strlen(n._author) + 1];
  // strcpy(_title, n._title);
  // strcpy(_author, n._author);
  _quantity = n._quantity;
}

// Explicit Copy Assignment Operator
Novel& Novel::operator=(const Novel& n) {
  // delete[] _title;
  // delete[] _author;

  // _title = new char[strlen(n._title) + 1];
  // _author = new char[strlen(n._author) + 1];
  // strcpy(_title, n._title);
  // strcpy(_author, n._author);
  _quantity = n._quantity;
  return *this;
}

// Explicit Move Constructor
Novel::Novel(Novel&& n) : Document(n), _author(n._author){
  _title = n._title;
  // _author = n._author;
  _quantity = n._quantity;
  // n._title = NULL;
  // n._author = NULL;
}

// Explicit Move Assignment Operator
Novel& Novel::operator=(Novel&& n) {
  // delete[] _title;
  // delete[] _author;

  _title = n._title;
  _author = n._author;
  _quantity = n._quantity;
  // n._title = NULL;
  // n._author = NULL;
  return *this;
}

Novel::~Novel() {
  // delete[] _title;
  // delete[] _author;
}

DocType Novel::getDocType() { return DOC_NOVEL; }

void Novel::print() {
  // printf("Novel, title: %s, author: %s, quantity: %d\n", _title.c_str(), _author.c_str(),
  //        _quantity);
  std::cout << "Novel, title: " << _title << ", author: " << _author << ", quantity: " << _quantity << std::endl;

}

void Novel::updateAuthor(const char *newAuthor) {
  // delete[] _author;
  // _author = new char[strlen(newAuthor) + 1];
  // strcpy(_author, newAuthor);
  _author = std::string(newAuthor);
}

const char *Novel::getAuthor() { return _author.c_str(); }

//==============================================================================

Comic::Comic(const char *title, const char *author, int issue, int quantity) : Document(title, quantity), _author(author){
  // _title = new char[strlen(title) + 1];
  // _author = new char[strlen(author) + 1];
  // strcpy(_title, title);
  // strcpy(_author, author);
  // _quantity = quantity;
  _issue = issue;
}

// Explicit Copy Constructor
Comic::Comic(const Comic& c) : Document(c), _author(c._author) {
  // _title = new char[strlen(c._title) + 1];
  // _author = new char[strlen(c._author) + 1];
  // strcpy(_title, c._title);
  // strcpy(_author, c._author);
  _quantity = c._quantity;
  _issue = c._issue;
}

// Explicit Copy Assignment Operator
Comic& Comic::operator=(const Comic& c) {
  // delete[] _title;
  // delete[] _author;

  // _title = new char[strlen(c._title) + 1];
  // _author = new char[strlen(c._author) + 1];
  // strcpy(_title, c._title);
  // strcpy(_author, c._author);
  _quantity = c._quantity;
  _issue = c._issue;
  return *this;
}

// Explicit Move Constructor
Comic::Comic(Comic&& c) : Document(c), _author(c._author) {
  // _title = c._title;
  // _author = c._author;
  _quantity = c._quantity;
  _issue = c._issue;
  // c._title = NULL;
  // c._author = NULL;
}

// Explicit Move Assignment Operator
Comic& Comic::operator=(Comic&& c) {
  // delete[] _title;
  // delete[] _author;

  _title = c._title;
  _author = c._author;
  _quantity = c._quantity;
  _issue = c._issue;
  // c._title = NULL;
  // c._author = NULL;
  return *this;
}

Comic::~Comic() {
  // delete[] _title;
  // delete[] _author;
}

DocType Comic::getDocType() { return DOC_COMIC; }

void Comic::print() {
  // printf("Comic, title: %s, author: %s, issue: %d, quantity: %d\n", _title.c_str(),
  //        _author.c_str(), _issue, _quantity);
  std::cout << "Comic, title: " << _title << ", author: " << _author << ", issue: " << _issue << ", quantity: " << _quantity << std::endl;

}

void Comic::updateAuthor(const char *newAuthor) {
  // delete[] _author;
  // _author = new char[strlen(newAuthor) + 1];
  // strcpy(_author, newAuthor);
  _author = std::string(newAuthor);
}

void Comic::updateIssue(int newIssue) { _issue = newIssue; }

const char *Comic::getAuthor() { return _author.c_str(); }
int Comic::getIssue() { return _issue; }

//==============================================================================

Magazine::Magazine(const char *title, int issue, int quantity) : Document(title, quantity){
  // _title = new char[strlen(title) + 1];
  // strcpy(_title, title);
  // _quantity = quantity;
  _issue = issue;
}

// Explicit Copy Constructor
Magazine::Magazine(const Magazine& m) : Document(m) {
  // _title = new char[strlen(m._title) + 1];
  // strcpy(_title, m._title);
  _quantity = m._quantity;
  _issue = m._issue;
}

// Explicit Copy Assignment Operator
Magazine& Magazine::operator=(const Magazine& m) {
  // delete[] _title;

  // _title = new char[strlen(m._title) + 1];
  // strcpy(_title, m._title);
  _quantity = m._quantity;
  _issue = m._issue;
  return *this;
}

// Explicit Move Constructor
Magazine::Magazine(Magazine&& m) : Document(m) {
  _title = m._title;
  _quantity = m._quantity;
  _issue = m._issue;
  // m._title = NULL;
}

// Explicit Move Assignment Operator
Magazine& Magazine::operator=(Magazine&& m) {
  // delete[] _title;

  _title = m._title;
  _quantity = m._quantity;
  _issue = m._issue;
  // m._title = NULL;
  return *this;
}

Magazine::~Magazine() {
  // delete[] _title;
}

DocType Magazine::getDocType() { return DOC_MAGAZINE; }

void Magazine::print()  {
  // printf("Magazine, title: %s, issue: %d, quantity: %d\n", _title.c_str(), _issue,
  //        _quantity);
  std::cout << "Magazine, title: " << _title << ", issue: " << _issue << ", quantity: " << _quantity << std::endl;

}

void Magazine::updateIssue(int newIssue) { _issue = newIssue; }
int Magazine::getIssue() { return _issue; }

//==============================================================================

Library::Library() {  };

Library::~Library() {
  // for (int i = 0; i < _docs_sz; i++)
  //   delete _docs[i];
}

int Library::addDocument(DocType t, const char *title, const char *author,
                         int issue, int quantity) {
  Document *d;
   std::unique_ptr<Document> c;
  switch (t) {
  case DOC_NOVEL: {
     c = std::make_unique<Novel>(title, author, quantity);
    d = c.release();
    break;
  }

  case DOC_COMIC: {
     c = std::make_unique<Comic>(title, author, issue, quantity);
     d = c.release();
    break;
  }

  case DOC_MAGAZINE: {
     c = std::make_unique<Magazine>(title, issue, quantity);
    d = c.release();
    break;
  }

  default:
    return 0;
  }
  return addDocument(d);
}

int Library::addDocument(Document *d) {
  if (searchDocument(d->getTitle()) != nullptr)
    return 0;

  _docs.push_back(d);
  return 1;
}

int Library::delDocument(const char *title) {
  int index = -1;
  for (size_t i = 0; i < _docs.size(); i++)
    if (!strcmp(_docs.at(i)->getTitle(), title)) {
      index = i;
      break;
    }

  if (index != -1) {
    _docs.erase(_docs.begin() + index);
    // for (int i = index + 1; i < _docs.size(); i++)
    //   _docs[i - 1] = _docs[i];
    // _docs_sz--;
    return 1;
  }

  return 0;
}

int Library::countDocumentOfType(DocType t) {
  int res = 0;

for (const auto& d : _docs) {
    if (d->getDocType() == t)
      res++;
    }
  return res;
}

Document *Library::searchDocument(const char *title) {
  for (const auto& d : _docs) {
    if (!strcmp(d->getTitle(), title))
      return d;
  }
  return nullptr;
}

void Library::print() {
  for (const auto& d : _docs) {
    d->print();}
}

int Library::borrowDoc(const char *title) {
  Document *d = searchDocument(title);
  if (d)
    return d->borrowDoc();
  return 0;
}

int Library::returnDoc(const char *title) {
  Document *d = searchDocument(title);
  if (d) {
    d->returnDoc();
    return 1;
  }
  return 0;
}

int Library::dumpCSV(const char *filename) {
  // char line[128];
  // int bytes_written;
  // int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  std::ofstream fd(filename); // added
  // if (fd == -1)
  //   return 0;
 if (!fd.is_open()) {    //added
        return 0;
    }
   for (const auto& d : _docs) {
        switch (d->getDocType()) {
        case DOC_NOVEL: {
            auto novel = dynamic_cast<Novel*>(d);
            if (novel) {
                fd << "novel," << novel->getTitle() << "," << novel->getAuthor() << ",," << novel->getQuantity() << "\n";
            }
            break;
        }

        case DOC_COMIC: {
            auto comic = dynamic_cast<Comic*>(d);
            if (comic) {
                fd << "comic," << comic->getTitle() << "," << comic->getAuthor() << ","
                        << comic->getIssue() << "," << comic->getQuantity() << "\n";
            }
            break;
        }

        case DOC_MAGAZINE: {
            auto magazine = dynamic_cast<Magazine*>(d);
            if (magazine) {
                fd << "magazine," << magazine->getTitle() << ",," << magazine->getIssue() << ","
                        << magazine->getQuantity() << "\n";
            }
            break;
        }

        default:
            return 0;
        }
    

    // bytes_written = write(fd, line, strlen(line));
    // if (bytes_written != static_cast<int>(strlen(line)))
    //   return 0;
  }

  // close(fd);
  return 1;
}
