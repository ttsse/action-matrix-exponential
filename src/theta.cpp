#include "expmv.h"

double expmv::theta_half_prec(int m)
{
switch(m)
{
    case 1:
        return 0.00195058476281490;
        break;
    case 2:
        return 0.0744366488703260;
        break;
    case 3:
        return 0.266455438985591;
        break;
    case 4:
        return 0.524204856864841;
        break;
    case 5:
        return 0.810268514288733;
        break;
    case 6:
        return 1.10822540384215;
        break;
    case 7:
        return 1.41081512609781;
        break;
    case 8:
        return 1.71493353771263;
        break;
    case 9:
        return 2.01902706794889;
        break;
    case 10:
        return 2.32246886135570;
        break;
    case 11:
        return 2.62492134557707;
        break;
    case 12:
        return 2.92629977789356;
        break;
    case 13:
        return 3.22657300191010;
        break;
    case 14:
        return 3.52578370683356;
        break;
    case 15:
        return 3.82397968085246;
        break;
    case 16:
        return 4.12122835471819;
        break;
    case 17:
        return 4.41759237158270;
        break;
    case 18:
        return 4.71313685841032;
        break;
    case 19:
        return 5.00792084833474;
        break;
    case 20:
        return 5.30200077643247;
        break;
    case 21:
        return 5.59542758397874;
        break;
    case 22:
        return 5.88824850385817;
        break;
    case 23:
        return 6.18050621001631;
        break;
    case 24:
        return 6.47223984123265;
        break;
    case 25:
        return 6.76348485176364;
        break;
    case 26:
        return 7.05427364278112;
        break;
    case 27:
        return 7.34463569778766;
        break;
    case 28:
        return 7.63459798213797;
        break;
    case 29:
        return 7.92418509850398;
        break;
    case 30:
        return 8.21341959917526;
        break;
    case 31:
        return 8.50232230999338;
        break;
    case 32:
        return 8.79091189654228;
        break;
    case 33:
        return 9.07920599508560;
        break;
    case 34:
        return 9.36722072360105;
        break;
    case 35:
        return 9.65497097994831;
        break;
    case 36:
        return 9.94247064386006;
        break;
    case 37:
        return 10.2297327700613;
        break;
    case 38:
        return 10.5167695629449;
        break;
    case 39:
        return 10.8035919244119;
        break;
    case 40:
        return 11.0902093188891;
        break;
    case 41:
        return 11.3766305965403;
        break;
    case 42:
        return 11.6628646913170;
        break;
    case 43:
        return 11.9489203001338;
        break;
    case 44:
        return 12.2348054433122;
        break;
    case 45:
        return 12.5205274825000;
        break;
    case 46:
        return 12.8060932750406;
        break;
    case 47:
        return 13.0915092215469;
        break;
    case 48:
        return 13.3767814472042;
        break;
    case 49:
        return 13.6619156356625;
        break;
    case 50:
        return 13.9469172721237;
        break;
    case 51:
        return 14.2317919280488;
        break;
    case 52:
        return 14.5165462025229;
        break;
    case 53:
        return 14.8011898763128;
        break;
    case 54:
        return 15.0857392837010;
        break;
    case 55:
        return 15.3702196120644;
        break;
    case 56:
        return 15.6546608892378;
        break;
    case 57:
        return 15.9390837779599;
        break;
    case 58:
        return 16.2234810794559;
        break;
    case 59:
        return 16.5078117631577;
        break;
    case 60:
        return 16.7920195108520;
        break;
    case 61:
        return 17.0760646886120;
        break;
    case 62:
        return 17.3599429227210;
        break;
    case 63:
        return 17.6436773003271;
        break;
    case 64:
        return 17.9272974337310;
        break;
    case 65:
        return 18.2108250605575;
        break;
    case 66:
        return 18.4942718659514;
        break;
    case 67:
        return 18.7776433519143;
        break;
    case 68:
        return 19.0609425039085;
        break;
    case 69:
        return 19.3441715448102;
        break;
    case 70:
        return 19.6273324788417;
        break;
    case 71:
        return 19.9104272097071;
        break;
    case 72:
        return 20.1934575614845;
        break;
    case 73:
        return 20.4764252844092;
        break;
    case 74:
        return 20.7593320588701;
        break;
    case 75:
        return 21.0421794990532;
        break;
    case 76:
        return 21.3249691563490;
        break;
    case 77:
        return 21.6077025225443;
        break;
    case 78:
        return 21.8903810328163;
        break;
    case 79:
        return 22.1730060685409;
        break;
    case 80:
        return 22.4555789599312;
        break;
    case 81:
        return 22.7381009885167;
        break;
    case 82:
        return 23.0205733894753;
        break;
    case 83:
        return 23.3029973538277;
        break;
    case 84:
        return 23.5853740305052;
        break;
    case 85:
        return 23.8677045385971;
        break;
    case 86:
        return 24.1499899440742;
        break;
    case 87:
        return 24.4322312747083;
        break;
    case 88:
        return 24.7144295295184;
        break;
    case 89:
        return 24.9965856741740;
        break;
    case 90:
        return 25.2787006425691;
        break;
    case 91:
        return 25.5607753385361;
        break;
    case 92:
        return 25.8428106381740;
        break;
    case 93:
        return 26.1248073940512;
        break;
    case 94:
        return 26.4067664445619;
        break;
    case 95:
        return 26.6886886364636;
        break;
    case 96:
        return 26.9705748791094;
        break;
    case 97:
        return 27.2524262703959;
        break;
    case 98:
        return 27.5342443752985;
        break;
    case 99:
        return 27.8160318088722;
        break;
    case 100:
        return 28.0977933868768;
        break;
}
};

double expmv::theta_single_prec(int m)
{
switch(m)
{
    case 1:
        return 1.19209279981543e-07;
        break;
    case 2:
        return 0.000597885889380522;
        break;
    case 3:
        return 0.0112338647352867;
        break;
    case 4:
        return 0.0511661936344509;
        break;
    case 5:
        return 0.130848716459947;
        break;
    case 6:
        return 0.249528932284670;
        break;
    case 7:
        return 0.401458242351048;
        break;
    case 8:
        return 0.580052462768877;
        break;
    case 9:
        return 0.779511337435803;
        break;
    case 10:
        return 0.995184079000446;
        break;
    case 11:
        return 1.22347954242414;
        break;
    case 12:
        return 1.46166150720903;
        break;
    case 13:
        return 1.70764852960870;
        break;
    case 14:
        return 1.95985058595990;
        break;
    case 15:
        return 2.21704439497472;
        break;
    case 16:
        return 2.47828087752197;
        break;
    case 17:
        return 2.74281711269878;
        break;
    case 18:
        return 3.01006636281763;
        break;
    case 19:
        return 3.27956121263600;
        break;
    case 20:
        return 3.55092621470650;
        break;
    case 21:
        return 3.82385742545097;
        break;
    case 22:
        return 4.09810697219151;
        break;
    case 23:
        return 4.37347131184050;
        break;
    case 24:
        return 4.64978222410076;
        break;
    case 25:
        return 4.92689984375591;
        break;
    case 26:
        return 5.20470722801236;
        break;
    case 27:
        return 5.48310608765863;
        break;
    case 28:
        return 5.76201340844777;
        break;
    case 29:
        return 6.04135875819257;
        break;
    case 30:
        return 6.32108212630196;
        break;
    case 31:
        return 6.60113217950116;
        break;
    case 32:
        return 6.88146484520972;
        break;
    case 33:
        return 7.16204215448776;
        break;
    case 34:
        return 7.44283129193660;
        break;
    case 35:
        return 7.72380381155399;
        break;
    case 36:
        return 8.00493498643629;
        break;
    case 37:
        return 8.28620326700217;
        break;
    case 38:
        return 8.56758982766258;
        break;
    case 39:
        return 8.84907818592395;
        break;
    case 40:
        return 9.13065388109011;
        break;
    case 41:
        return 9.41230420221943;
        break;
    case 42:
        return 9.69401795696303;
        break;
    case 43:
        return 9.97578527447070;
        break;
    case 44:
        return 10.2575974367975;
        break;
    case 45:
        return 10.5394467342422;
        break;
    case 46:
        return 10.8213263408522;
        break;
    case 47:
        return 11.1032302069807;
        break;
    case 48:
        return 11.3851529663092;
        break;
    case 49:
        return 11.6670898551789;
        break;
    case 50:
        return 11.9490366424294;
        break;
    case 51:
        return 12.2309895682315;
        break;
    case 52:
        return 12.5129452906449;
        break;
    case 53:
        return 12.7949008388429;
        break;
    case 54:
        return 13.0768535721261;
        break;
    case 55:
        return 13.3588011439872;
        break;
    case 56:
        return 13.6407414705053;
        break;
    case 57:
        return 13.9226727022214;
        break;
    case 58:
        return 14.2045931986367;
        break;
    case 59:
        return 14.4865015050251;
        break;
    case 60:
        return 14.7683963322188;
        break;
}
};

double expmv::theta_double_prec(int m)
{
switch(m)
{
    case 1:
        return 2.22044604925031e-16;
        break;
    case 2:
        return 2.58095680299462e-08;
        break;
    case 3:
        return 1.38634786611912e-05;
        break;
    case 4:
        return 0.000339716883997683;
        break;
    case 5:
        return 0.00240087635788727;
        break;
    case 6:
        return 0.00906565640759510;
        break;
    case 7:
        return 0.0238445553250027;
        break;
    case 8:
        return 0.0499122887111532;
        break;
    case 9:
        return 0.0895776020322334;
        break;
    case 10:
        return 0.144182976161438;
        break;
    case 11:
        return 0.214235806845171;
        break;
    case 12:
        return 0.299615891381158;
        break;
    case 13:
        return 0.399777533631680;
        break;
    case 14:
        return 0.513914693612429;
        break;
    case 15:
        return 0.641083523304120;
        break;
    case 16:
        return 0.780287425662658;
        break;
    case 17:
        return 0.930532846078657;
        break;
    case 18:
        return 1.09086371929004;
        break;
    case 19:
        return 1.26038106064264;
        break;
    case 20:
        return 1.43825259680434;
        break;
    case 21:
        return 1.62371595023582;
        break;
    case 22:
        return 1.81607781621509;
        break;
    case 23:
        return 2.01471078094462;
        break;
    case 24:
        return 2.21904886936509;
        break;
    case 25:
        return 2.42858252444283;
        break;
    case 26:
        return 2.64285345745944;
        break;
    case 27:
        return 2.86144963393426;
        break;
    case 28:
        return 3.08400054498916;
        break;
    case 29:
        return 3.31017283989027;
        break;
    case 30:
        return 3.53966634874369;
        break;
    case 31:
        return 3.77221049568175;
        break;
    case 32:
        return 4.00756108611804;
        break;
    case 33:
        return 4.24549744257970;
        break;
    case 34:
        return 4.48581985944737;
        break;
    case 35:
        return 4.72834734579354;
        break;
    case 36:
        return 4.97291562619198;
        break;
    case 37:
        return 5.21937537108406;
        break;
    case 38:
        return 5.46759063052454;
        break;
    case 39:
        return 5.71743744757201;
        break;
    case 40:
        return 5.96880263004185;
        break;
    case 41:
        return 6.22158266168989;
        break;
    case 42:
        return 6.47568273607998;
        break;
    case 43:
        return 6.73101589838102;
        break;
    case 44:
        return 6.98750228213063;
        break;
    case 45:
        return 7.24506842959795;
        break;
    case 46:
        return 7.50364668578886;
        break;
    case 47:
        return 7.76317465737799;
        break;
    case 48:
        return 8.02359472893998;
        break;
    case 49:
        return 8.28485362980392;
        break;
    case 50:
        return 8.54690204568493;
        break;
    case 51:
        return 8.80969426997132;
        break;
    case 52:
        return 9.07318789017615;
        break;
    case 53:
        return 9.33734350561201;
        break;
    case 54:
        return 9.60212447282656;
        break;
    case 55:
        return 9.86749667575340;
        break;
    case 56:
        return 10.1334283178975;
        break;
    case 57:
        return 10.3998897341910;
        break;
    case 58:
        return 10.6668532204341;
        break;
    case 59:
        return 10.9342928784758;
        break;
    case 60:
        return 11.2021844755046;
        break;
    case 61:
        return 11.4705053160025;
        break;
    case 62:
        return 11.7392341250802;
        break;
    case 63:
        return 12.0083509420532;
        break;
    case 64:
        return 12.2778370232469;
        break;
    case 65:
        return 12.5476747531264;
        break;
    case 66:
        return 12.8178475629466;
        break;
    case 67:
        return 13.0883398562033;
        break;
    case 68:
        return 13.3591369402429;
        break;
    case 69:
        return 13.6302249634550;
        break;
    case 70:
        return 13.9015908575319;
        break;
    case 71:
        return 14.1732222843318;
        break;
    case 72:
        return 14.4451075869313;
        break;
    case 73:
        return 14.7172357444901;
        break;
    case 74:
        return 14.9895963305943;
        break;
    case 75:
        return 15.2621794747717;
        break;
    case 76:
        return 15.5349758269057;
        break;
    case 77:
        return 15.8079765243009;
        break;
    case 78:
        return 16.0811731611740;
        break;
    case 79:
        return 16.3545577603693;
        break;
    case 80:
        return 16.6281227471121;
        break;
    case 81:
        return 16.9018609246349;
        break;
    case 82:
        return 17.1757654515241;
        break;
    case 83:
        return 17.4498298206474;
        break;
    case 84:
        return 17.7240478395392;
        break;
    case 85:
        return 17.9984136121263;
        break;
    case 86:
        return 18.2729215216918;
        break;
    case 87:
        return 18.5475662149805;
        break;
    case 88:
        return 18.8223425873590;
        break;
    case 89:
        return 19.0972457689506;
        break;
    case 90:
        return 19.3722711116726;
        break;
    case 91:
        return 19.6474141771086;
        break;
    case 92:
        return 19.9226707251543;
        break;
    case 93:
        return 20.1980367033831;
        break;
    case 94:
        return 20.4735082370831;
        break;
    case 95:
        return 20.7490816199359;
        break;
    case 96:
        return 21.0247533053561;
        break;
    case 97:
        return 21.3005198986635;
        break;
    case 98:
        return 21.5763781507214;
        break;
    case 99:
        return 21.8523249549901;
        break;
    case 100:
        return 22.1283573534646;
        break;
}
};