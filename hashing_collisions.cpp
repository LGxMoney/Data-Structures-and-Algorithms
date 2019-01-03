  /**
   *Calculates the number of collisions for a 
   *given hash function
   *@author Garrett Money
   *@version March 19, 2018
  */

  #include <cstdint>
  #include <iomanip>
  #include <iostream>
  #include <fstream>

  using namespace std;

  //prototypes for two separate hash functions
  size_t hash_320( const string & key, size_t table_size );
  size_t custom_hash_320( const string & key, size_t table_size );

  /**
   *Main method to test two collisions for two different functions
   *@returns 0
   */
  int main()
  {
    //number of words in desired file found with wc -w <filename>
    const size_t word_count = 99171;

    //variables to count number of collisions for each hash function
    size_t funct1_collisions = 0;
    size_t funct2_collisions = 0;

    //arrays to store whether or not a collision has occurred followed
    size_t hash_table [ word_count ];
    size_t custom_hash_table [ word_count ];

    //stores the current word and the computed hash keys
    string current_word;
    size_t hash_key_1;
    size_t hash_key_2;

    //file declarations
    ifstream file;
    file.open( "/usr/share/dict/words" );

    //initialize arrays to a number the key can never be
    for( uint i = 0; i < word_count; i++ )
    {
      hash_table[ i ] = word_count + 1;
      custom_hash_table[ i ] = word_count + 1;
    }

    //read from the file word by word and store into current_word
    while( getline( file, current_word ) )
    {
      //call appropriate functions and store hashed value
      hash_key_1 = hash_320( current_word, word_count );
      hash_key_2 = custom_hash_320( current_word, word_count );

      //if the hashed index is the first key there, update it
      if( hash_table[ hash_key_1 ]  == ( word_count + 1 ) )
      {
	hash_table[ hash_key_1 ] = hash_key_1;
      }
      //if the value is not what the original was, a collision has occurred
      else
      {
	funct1_collisions++;
      }

      //if the hashed index is the first key there, update it 
      if( custom_hash_table[ hash_key_2 ] == ( word_count + 1 ) )
      {
	custom_hash_table[ hash_key_2 ] = hash_key_2;
      }
      //if the value is not what the original was, a collision has occurred
      else
      {
	funct2_collisions++;
      }  
    }

    //print out the number of collisions for each function
    cout << funct1_collisions << endl;
    cout << funct2_collisions << endl;
    
    return 0;
  }

  /**
   *This function takes a word and calculates a key based off of the 
   *ASCII values of the individual letters
   *@author Jon Beck
   *@param key is the word read from the file
   *@param table_size is the size of m, or the size of the hash table
   *@return the calculated hash value
   */
  size_t hash_320( const string & key, size_t table_size )
  {
    size_t hash_val = 0;

    for( auto character : key )
    {
      hash_val = 37 * hash_val + static_cast< unsigned char >( character );
    }
    return hash_val % table_size;
  }

  /**
   *This function takes a word and calculates a key based off of the 
   *ASCII values of the individual letters
   *source: 
   *  https://www.javamex.com/tutorials/collections/
   *  hash_function_technical_2.shtml
   *@param key is the word read from the file
   *@param table_size is the size of m, or the size of the hash table
   *@return the calculated hash value
   */
  size_t custom_hash_320( const string & key, size_t table_size )
  {
    size_t hash_val = 0;

    for( auto character : key )
    {
      hash_val = ( hash_val << 5 ) - hash_val +
	static_cast< unsigned char >( character );
    }
    return hash_val % table_size;
  }
