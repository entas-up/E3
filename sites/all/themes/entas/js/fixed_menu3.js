var num = 115; //number of pixels before modifying styles

jQuery(window).bind('scroll', function () {
    if (jQuery(window).scrollTop() > num) {
        jQuery('.scroll-menu').addClass('fixed');
		jQuery('.scroll-logo').addClass('fixed-logo');
    } else {
        jQuery('.scroll-menu').removeClass('fixed');
		jQuery('.scroll-logo').removeClass('fixed-logo');
    }
});