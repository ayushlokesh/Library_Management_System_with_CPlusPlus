#pragma once
#include <string>

/* The different types of documents stored in the library */
enum DocType{ DOC_NOVEL, DOC_COMIC, DOC_MAGAZINE };

/* Parent class for all types of documents */
class Document {
public:
  Document();
  Document(const char* title, const int qty);
  virtual ~Document();

  /* return the document type (abstract method) */
  virtual DocType getDocType() = 0;

  /* print the document attributes in a single line on the standard output
   * (abstract method), the format for the various document types is as
   * follows:
   * Novel, title: <title>, author: <author>, quantity: <quantity>
   * Comic, title: <title>, author: <author>, issue: <issue>, quantity: <quantity>
   * Magazine, title: <title>, issue: <issue>, quantity: <quantity>
   */
  virtual void print() = 0;

  /* setters and getters */
  void updateTitle(const char* newTitle);
  void updateQuantity(int newQuantity);
  const char* getTitle();
  int getQuantity();

  /* Used when someone tries to borrow a document, should return 1 on success
   * and 0 on failure */
  bool borrowDoc();

  /* Used when someone returns a document */
  void returnDoc();

protected:
  /* These need to be protected to be inherited by the child classes */
  std::string _title;  // document title
  int _quantity; // quantity held in the library, should be updated on
                 // borrow (-1) and return (+1)

  /* Copying or moving abstract objects is risky, but the derived objects
   * might need them to implement their default copy/move methods, so we
   * make them protected */
  Document(const Document& doc);
  Document& operator=(const Document& doc);
  Document(Document&& doc);
  Document& operator=(Document&& doc);
};

class Novel : public Document {
public:
  Novel(const char* title, const char* author, int quantity);

  // Copying or moving concrete subclasses of abstract classes is okay
  Novel(const Novel& n);
  Novel& operator=(const Novel& n);
  Novel(Novel&& n);
  Novel& operator=(Novel&& n);

  ~Novel();

  /* virtual function overrides */
  DocType getDocType() override;
  void print() override;

  /* getters and setters */
  void updateAuthor(const char *newAuthor);
  const char* getAuthor();

private:
  /* In addition to the base Document's attributes, a novel has an author */
  std::string _author;
};

class Comic : public Document {
public:
  Comic(const char* title, const char* author, int issue, int quantity);

  // Copying or moving concrete subclasses of abstract classes is okay
  Comic(const Comic& n);
  Comic& operator=(const Comic& n);
  Comic(Comic&& n);
  Comic& operator=(Comic&& n);

  ~Comic();

  /* virtual function overrides */
  DocType getDocType() override;
  void print() override;

  /* getters, setters */
  void updateAuthor(const char *newAuthor);
  void updateIssue(int newIssue);
  const char *getAuthor();
  int getIssue();

private:
  /* In addition to the base Document's attributes, a comic has an author as
   * well as an issue number */
  std::string _author;
  int _issue;
};

class Magazine : public Document {
public:
  Magazine(const char* title, int issue, int quantity);

  // Copying or moving concrete subclasses of abstract classes is okay
  Magazine(const Magazine& n);
  Magazine& operator=(const Magazine& n);
  Magazine(Magazine&& n);
  Magazine& operator=(Magazine&& n);

  ~Magazine();

  /* virtual function overrides */
  DocType getDocType() override;
  void print() override;

  /* getters, setters */
  void updateIssue(int newIssue);
  int getIssue();

private:
  /* In addition to the base Document's attributes, a magazine has an issue
   * number */
  int _issue;
};

/* 0ne instance of that class represents a library */
#include <vector>
class Library {
public:
  Library();
  ~Library();

  /* print the entire library on the standard output, one line per document,
   * in the order they were inserted in the library, using the print()
   * methods implemented by the document objects */
  void print() ;

  /* Dump the library in a CSV file. The format is:
   * 1 line per file:
   * <document type>,<title>,<author>,<issue>,<quantity>
   * A field not relevant for a given document type (e.g. issue for novel)
   * is left blank. Return 1 on success, 0 on failure. */
  int dumpCSV(const char* filename);

  /* Search for a document in the library, based on the title. We assume that
   * a title identifies uniquely a document in the library, i.e. there cannot
   * be 2 documents with the same title. Returns a pointer to the document if
   * found, NULL otherwise */
  Document* searchDocument(const char* title);

  /* Add/delete a document to/from the library, return 1 on success and
   * 0 on failure.  */
  int addDocument(DocType t, const char* title, const char* author, int issue, int quantity);
  int delDocument(const char* title);

  /* Same but add a pre-existing document. The caller relinquishes ownership of
   * the Document. Return 1 on success and 0 on failure. */
  int addDocument(Document* d);

  /* Count the number of documents of a given type present in the library */
  int countDocumentOfType(DocType t);

  /* Borrow/return documents, return 1 on success, 0 on failure */
  int borrowDoc(const char* title);
  int returnDoc(const char* title);

private:
  /* Array big enough to hold all documents in the library.
   * It's safe to assume that there will never be more than 32K
   * documents in the array.*/
  std::vector<Document*>  _docs;
};
