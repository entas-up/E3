CKEDITOR.plugins.add( 'sbutton', {
    icons: 'sbutton',
    init: function( editor ) {
        editor.addCommand( 'special button', {
            
                exec: function( editor ) {

                editor.insertHtml( '<div class="special-button fa fa-file-o fa-2x">&nbspЗамените текст сообщения&nbsp</div>' );
            }
        });
        editor.ui.addButton( 'special button', {
            label: 'Insert special button',
			icon : this.path + 'icons/sbutton.png',
            command: 'special button',
            toolbar: 'insert'
        });
    }
});