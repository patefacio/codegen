module phone.phone;

struct Address { 
  string street;
  string zipCode;
  string state;
  string country;
  // custom <dstruct address public_section>
  // end <dstruct address public_section>
}

struct AddressBook { 
  alias Address[string] EmailAddressMap;
  // custom <dstruct address_book public_section>
  // end <dstruct address_book public_section>

  private {
    EmailAddressMap _emailAddressMap;
  }
}


static if(1) unittest { 
// custom <dmodule phone unittest>
// end <dmodule phone unittest>
}

/**
   Copyright: 2012 by Daniel Davidson
   All rights reserved.
*/
