================================
pure-tags: XML/HTML DSL for Pure
================================

..default-domain:: pure
..module:: tags


Mike maul <mike.maul@gmail.com>

This modules allows the definition of an XMLish tag structure in a as a term.
Structure definitions can then be used to render a textual XML 
representation. The main goal is to ease the simplify the construction of 
HTML documents generated in a pure progam.
  

Installation
============

Run ``make`` to compile the module and ``make install`` (as root) to install
it in the Pure library directory. This requires GNU make, and of course you
need to have Pure installed. 

``make`` tries to guess your Pure installation directory and platform-specific
setup. If it gets this wrong, you can set some variables manually. In
particular, ``make install prefix=/usr`` sets the installation prefix, and
``make PIC=-fPIC`` or some similar flag might be needed for compilation on 64
bit systems. 

Other useful build targets are

html
  builds html documentation
pdf
  builds pdf documentation
dist
  build distrubtuion copy of source package
clean 
  removes all generated and compiled files 
 
Usage
=====

To use this module place the following in your program
  using tags;

The tag DSL type signature is shown below: 
|    tag = symbol|string record list of tags|string|tag
The following are examples of valid tags:

::

  > frag1 = h1 {style=>"background-color:red;"} "Hello";
  > thtmli::render_tags (frag1);
  "<h1 style='background-color:red;' >Hello</h1>"

  > frag2 = p {} (span {class => "emp"} "This is an imporant message.");
  > thtmli::render_tags (frag2);
  "<p ><span classS='emp' >This is an imporant message.</span></p>"

  > frag3 = tr {} [th {} "Col 1",th {} "Col 2",th {} "Col 3"];
  > thtmli::render_tags (frag3);
  "<tr ><th >Col 1</th><th >Col 2</th><th >Col 3</th></tr>"
  
Some things to notice is that parenthesis are necessary to force pure to 
interpet the expression as a single argument. You can also use brackets 
for grouping the expression into a list element and is useful if you 
intented to add sibling tags later. To avoid collisions with keywords 
and other defined symbols you can use a string for the tag istead 
of a symbol as shown below.

|  > frag4 = "div" {} "hello";
|  > thtmli::render_tags (frag4);
|  "<div >hello</div>"

The following is an example of a more complicated expression:

|  > tags::render_tags (html {} [body {} 
|
|      [form {action=>""} [fieldset {} [
|       legend {} "Contact Info:",
|       "Name:",  input {"type" => "text", size => 32} [],
|       "Email:", input {"type" => "text", size => 48} [],
|       "Phone:", input {"type" => "text", size => 12} []
|    ]]]]);
|   "<html ><body ><form action='' ><fieldset ><legend >Contact Info:</legend>Name:<input type='text' size='32' ></input>Email:<input type='text' size='48' ></input>Phone:<input type='text' size='12' ></input></fieldset></form></body></html>"

Combining expressions
---------------------
Since the siblings can be grouped as lists they also can be combined with list 
operators.

::
> thtmli::render_tags ([hr {} ""] + [hr {} ""]);
"<hr ></hr><hr ></hr>"

> thtmli::render_tags ( HR {} "" :  HR {} "" : []);
"<HR ></HR><HR ></HR>"
> 


---------

Goto: `API
<pure-tags.html>`_.

