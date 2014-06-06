$(function(){
        // Check the initial Poistion of the Sticky Header
        var stickyHeaderTop = $('#navigation').offset().top;
 
        $(window).scroll(function(){
                if( $(window).scrollTop() > stickyHeaderTop ) {
                        $('#navigation').css({position: 'fixed', top: '0px'});
                        
                } else {
                        $('#navigation').css({position: 'static', top: '0px'});
                        
                }
        });
  })(jQuery);