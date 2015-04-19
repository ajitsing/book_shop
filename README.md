# book_shop
A basic project to manage a book inventory

Its a command line tool to manage a bookshop
The available books are present in BooksInventory.txt


######bookshop search "Paulo"
	will search Paulo under Author,Title,Publication,ISBN & Price
	and display the results as:-
	ISBN			Price		Author		Title			Publisher
	8172234988	200		Paulo Coelho	The Alchemist	Harper Collins Publishers

######bookshop search -author "Paulo"
	will search Paulo under Author
	and display the results as:-
	ISBN			Price		Author		Title			Publisher
	8172234988	200		Paulo Coelho	The Alchemist	Harper Collins Publishers

######bookshop search -title "Alchemist"
	will search Alchemist under Title
	and display the results as:-
	ISBN			Price		Author		Title			Publisher
	8172234988	200		Paulo Coelho	The Alchemist	Harper Collins Publishers
	
######bookshop search -publisher "Harper Collins"
	will search Harper Collins under publisher
	and display the results as:-
	ISBN			Price		Author		Title			Publisher
	8172234988	200		Paulo Coelho	The Alchemist	Harper Collins Publishers
	000729980X	144		Agatha Christie	The Clocks	Harper Collins UK
	
######bookshop search -isbn "0571283071"
	will search 0571283071 under isbn
	and display the results as:-
	ISBN			Price		Author		Title			Publisher
	0571283071	374		Jeet Thayil		Narcopolis		Faber & Faber
	
######bookshop add "isbn:0007258917;price:245;author:Jhumpa Lahiri;title:The Namesake;publisher:Harper Collins India"
	will add the book to the inventory

######bookshop remove -isbn "0007258917"
	will remove the book by isbn in the BooksInventory.txt
