#include <iostream>
#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;


int main() {
  // FILESYSTEM
  /*
    The features of the std::filesystem library that we'll use are:

    . fs::path
    - can be constructed from a std::string
    - has a member function called 'string'

    . fs::directory_entry
    - can be constructed from an fs::path
    - has a member function called 'path'
    - has a predicate member function called 'is_directory'
    - has a predicate member function called 'is_regular_file'

    . fs::directory_iterator
    - can be constructed from an fs::path;
    returns an iterator to the first entry
    of the specified directory
    - has a dereferencing operator that returns
    a reference to const fs::directory_entry
    - has an arrow operator that returns
    a pointer to const fs::directory_entry
    - a default constructed fs::directory_iterator
    is used to indicate "past-the-end"
    - so that range-based for loops are available...
    - begin(it) == it
    -   end(it) == fs::directory_iterator()
  */
  std::cout << "current path: " << fs::current_path().string() << "\n\n";

  fs::path   directory("directory");
  fs::path  input_path("in.txt");
  fs::path nicely_idxt("nicely_indexed.txt");
  fs::path output_path("out.txt");

  std::cout <<   directory.string() << '\n';
  std::cout <<  input_path.string() << '\n';
  std::cout << nicely_idxt.string() << '\n';
  std::cout << output_path.string() << "\n\n";


  fs::directory_entry de1(directory);
  fs::directory_entry de2(input_path);
  fs::directory_entry de3(nicely_idxt);
  fs::directory_entry de4(output_path);

  std::cout << de1.path().string() << '\n';
  std::cout << de2.path().string() << '\n';
  std::cout << de3.path().string() << '\n';
  std::cout << de4.path().string() << "\n\n";

  std::cout << de1.is_directory() << ' ';
  std::cout << de2.is_directory() << ' ';
  std::cout << de3.is_directory() << ' ';
  std::cout << de4.is_directory() << '\n';

  std::cout << de1.is_regular_file() << ' ';
  std::cout << de2.is_regular_file() << ' ';
  std::cout << de3.is_regular_file() << ' ';
  std::cout << de4.is_regular_file() << "\n\n";  // 0 the first time, 1 the second time
  // because out.txt is written further down

  fs::directory_iterator it(directory);

  std::cout << (*it).path().string() << '\n';
  std::cout <<   it->path().string() << "\n\n";


  std::cout << (begin(it) == it)                       << ' ';
  std::cout <<   (end(it) == fs::directory_iterator()) << "\n\n";


  while (it != fs::directory_iterator()) {
    std::cout << it->path().string()   << ' ';
    std::cout << it->is_directory()    << ' ';
    std::cout << it->is_regular_file() << '\n';

    ++it;
  }
  std::cout << '\n';


  for (auto entry : fs::directory_iterator(directory)) {
    std::cout << entry.path().string()   << ' ';
    std::cout << entry.is_directory()    << ' ';
    std::cout << entry.is_regular_file() << '\n';
  }
  std::cout << '\n';

  fs::create_directory("source_directory");
  fs::copy("source_directory", "destination_directory", fs::copy_options::recursive);
  fs::remove_all("source_directory");
  std::ofstream file("source_file.txt");
  file.close();
  fs::copy("source_file.txt", "destination_file.txt");
  fs::remove("source_file.txt");



  /*
    To read and write files we need file stream...
  */


  // RETHINKING COUT AND CIN, IOSTREAM
  // std::string  for_giving_to_the_output_stream = "output";
  // std::cout << for_giving_to_the_output_stream << std::endl;

  // std::string for_receiving_from_the_input_stream;
  // std::cin >> for_receiving_from_the_input_stream;

  /*
    The arrows << and >> indicate the flow of characters.

    std::cout << for_giving_to_the_output_stream takes
    the characters stored by for_giving_to_the_output_stream
    and gives a copy of them to the console output stream.

    At various intervals, the console output stream
    flushes its characters and displays them in the console.

    ASIDE... The difference between '\n' and std::endl
    is that std::endl forces the console output stream to
    flush its characters and display them in the console.
    Using '\n' can sometimes result in a delayed output.
    However, using std::endl results in slower code.

    std::cin >> for_receiving_from_the_input_stream takes
    some of the characters stored in the console input stream,
    and gives them to for_receiving_from_the_input_stream.
  */


  // FILE STREAMS
  /*
    If we make a file output stream called fout, then
    fout << for_giving_to_the_output_stream takes
    the characters stored by for_giving_to_the_output_stream
    and gives a copy of them to the file output stream.

    At various intervals, the file output stream
    flushes its characters and writes them to a file.

    If we make a file input stream called fin, then
    fin >> for_receiving_from_the_input_stream takes
    some of the characters stored in the file input stream,
    and gives them to for_receiving_from_the_input_stream.
  */


  /*
    RECALL INHERITANCE AND POLYMORPHISM
    std::ofstream inherits from std::ostream and
    std::ifstream inherits from std::istream,

    This means that...
    - as soon as you've written
    operator<< for writing to the console,
    it works just as well for file writing;
    - as soon as you've written
    operator>> for reading from the console,
    it works just as well for file reading.

    It's also a reason to expect that
    anything you can do with console streams,
    you can do with file streams.
  */


  // Construct a file output stream using the output path.
  std::ofstream fout(output_path);

  for (size_t i = 1; i < 1000; ++i) {
    // Writes to the file specified by output_path.
    // Due to the '\n', this is one line's worth.
    // '\n' is more efficient than std::endl here.
    fout << "This is line " << i << '\n';
  }
  // The final line does not have a '\n'.
  fout << "This is line " << 1000;

  // We are well behaved and close the file stream.
  fout.close();


  // Construct a file input stream using the input path.
  std::ifstream fin(input_path);
  std::string line;

  while (true) {
    // 'getline' behaves almost the same as it did for std::cin.
    // There's a buffer containing the file contents.
    //  - 'getline' grabs characters from the buffer
    //    until it encounters a '\n' or the end of the buffer.
    //  - The characters before '\n' are stored in 'line'.
    //  - Finally, 'getline' moves past the '\n' it stopped at.
    getline(fin, line);

    // When using getline(std::cin, line),
    // if the end of the buffer has been reached,
    // a user is prompted to add more characters
    // to the buffer by typing in the console.

    // For getline(fin, line),
    // if the end of the buffer has been reached,
    // fin.fail() will become true so that
    // static_cast<bool>(fin) == !fin.fail()
    // becomes false. This allows us to break.
    if (fin) {
      std::cout << line << '\n';
    }
    else {
      break;
    }
  }
  // We are well behaved.
  fin.close();
  std::cout << '\n';




  /*
    Some other useful member functions of ifstreams are:
    - tellg - returns the position of the current character in the input stream
    - seekg - sets the position of the next character to be extracted from the input stream
    - read  - extracts characters from the stream and stores them starting at a specified char*.
  */

  std::string   str(10, 'z');
  std::ifstream demo(nicely_idxt);
  std::cout << str << ' ' << demo.tellg() << '\n';
  demo.read(&str[0], 3);          std::cout << str << ' ' << demo.tellg() << '\n';
  demo.seekg(7);                  std::cout << str << ' ' << demo.tellg() << '\n';
  demo.read(&str[5], 3);          std::cout << str << ' ' << demo.tellg() << '\n';
  demo.seekg(0);                  std::cout << str << ' ' << demo.tellg() << '\n';
  demo.read(&str[0], 10);         std::cout << str << ' ' << demo.tellg() << '\n';
  demo.read(&str[8], 1);          std::cout << str << ' ' << demo.tellg() << '\n';
  demo.close();

  // One can open a std::ifstream with
  // tellg() equal to the file length
  // by using std::ios::ate when
  // constructing the std::ifstream.
  std::ifstream demo2(nicely_idxt, std::ios::ate);
  std::cout << '\n' << demo2.tellg() << '\n';
  demo2.close();




  return 0;
}
