/**
 * Cumulus for Drupal
 * README.txt
 */

Cumulus is a module that provides a beautiful, Flash-based 3D tag cloud implementation.
It is based on Roy Tanck's WordPress module called WP-Cumulus (see http://wordpress.org/extend/plugins/wp-cumulus/)


/**
 * Installing (VERY IMPORTANT!)
 */

- After you put Cumulus in your sites/all/modules or sites/default/modules (or where ever you put them :-) you need one more file...
- That file is cumulus.js (which can't be put on drupal.org since its not licensed under GPL.)
- Get that file from http://pratul.in/files/cumulus.js
- Put in your Cumulus folder.
- That's it!


/**
 * Frequently Asked Questions
 */

= Cumulus is breaking my theme for anonymous users and not displaying
at all/correctly. Help!
- Unfortunately, block caching in Drupal 6 is on a per-role basis. Thus
it will break Cumulus if its turned on your site. Turn it off and
Cumulus will be happy. You can find the settings on admin/settings/performance
