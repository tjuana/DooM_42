/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:05:31 by drafe             #+#    #+#             */
/*   Updated: 2020/01/26 22:32:59 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	void end_game(t_new_player *pl)
**	Function to end game
** **************************************************************************
*/

void	end_game(t_new_player *pl)
{	
	//// printf "END OF GAME!!!"
	SDL_Delay(50);
	//free and clean all old stuff
	if (pl)
		free(pl);
	exit(EXIT_SUCCESS);
}

/*
** **************************************************************************
**	t_new_player *load_next(t_new_player *pl)
**	Function to open next map
** **************************************************************************
*/

t_new_player		*load_next(t_new_player *pl)
{
	t_new_player	*pl_next;

	pl_next = NULL;
	if (pl->lvl == NULL)
		end_game(pl);
	if (!(pl_next = (t_new_player *)malloc(sizeof(t_new_player))))
	{
		ft_putstr_fd("load_next malloc error.\n", 2);
		exit(EXIT_FAILURE);
	}
	pl_next->sectors_nb = 0;
	pl_next->win = pl->win;
	load_file(pl->lvl, pl_next);
	pl->srf ? SDL_FreeSurface(pl->srf) : 0;
	pl->srf = NULL;
	//free(pl);
	pl = NULL;
	pl = pl_next;
	pl->srf = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0);
	!pl->srf ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	pl->rend = SDL_GetRenderer(pl->win);
	!pl->rend ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	return(pl);
}

/*
** **************************************************************************
**	int but_script(t_new_player *pl, int sec_nb, t_subevents *se)
**	Function to do button scipts
** **************************************************************************
*/

void	load_file(char *ag, t_new_player *pl)//this function reads a new map format
{
	// printf("ag===|%s|\n", ag);
    FILE* fp = fopen(ag, "rt");
	
    if(!fp) { perror(ag); exit(EXIT_FAILURE); }
    char Buf[256];
    char word[256];
    char *ptr;
    float angle;
    t_new_xy *vert = NULL;//, v;
    t_new_xy v;
    int n;
    int m;
	int nb_vert;
    int p;//the first time is 0. Is a rule for all statics variables
	//int	p;
	//p = 0;
    
	p = 0;
	nb_vert = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
				ft_putstr("load VERTXX\n");
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                { vert = realloc(vert, ++nb_vert * sizeof(*vert)); vert[nb_vert-1] = v; }
                break;
            case 's': // sector
				ft_putstr("load SEC\n");
                if(p == 0)
                {
                    pl->sectors = malloc(pl->sectors_nb * sizeof(*pl->sectors));//allocate memory if first time
                    p++;
                }
                pl->sectors = realloc(pl->sectors, ++pl->sectors_nb * sizeof(*pl->sectors));//reallocate memory
                t_new_sector  *sect = &pl->sectors[pl->sectors_nb - 1];//SECT CREATED
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor, &sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                {
					num = realloc(num, ++m * sizeof(*num));
					num[m-1] = word[0]=='x' ? -1 : atoi(word);
				}
                sect->npoints = m /= 2;
                sect->vertex = malloc((m + 1) * sizeof(*sect->vertex));
				for(n = 0; n < m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
				m == 2 ? m = 3 : m;
                sect->neighbors = malloc((m) * sizeof(*sect->neighbors));
				for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
                free(num);
                break;
			case 'l':
				if (!(pl->lvl = (char *)malloc(sizeof(char) * 512)))
				{
					ft_putstr_fd("lvl path malloc error", 2);
					exit(EXIT_FAILURE);
				}
				sscanf(ptr += n, "%s", pl->lvl);
				break;
            case 'p':; // player
				ft_putstr("load PLAY\n");
                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player_init(pl, &v, &angle, &n); // TODO: Range checking
                pl->where.z = pl->sectors[pl->sector].floor + EYE_H;
			
        }
    fclose(fp);
    free(vert);
}

/*
void LoadData(char *ag, t_new_player *pl)//this function reads a new map format
{
    FILE* fp = fopen(ag, "rt");
    if(!fp) { perror(ag); exit(EXIT_FAILURE); }
    char Buf[256];
    char word[256];
    char *ptr;
    float angle;
    t_new_xy *vert = NULL;//, v;
    t_new_xy v;
    int n;
    int m;
    static int p;//the first time is 0. Is a rule for all statics variables
    int NumVertices = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                if(p == 0)
                {
                    pl->sectors = malloc(pl->sectors_nb * sizeof(*pl->sectors));//allocate memory if first time
                    p++;
                }
                pl->sectors = realloc(pl->sectors, ++pl->sectors_nb * sizeof(*pl->sectors));//reallocate memory
                t_new_sector  *sect = &pl->sectors[pl->sectors_nb - 1];//SECT CREATED
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                { num = realloc(num, ++m * sizeof(*num)); num[m-1] = word[0]=='x' ? -1 : atoi(word); }
                sect->npoints = m /= 2;
                sect->vertex    = malloc((m + 1) * sizeof(*sect->vertex));
				for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
				m == 2 ? m = 3 : m;
                sect->neighbors = malloc((m) * sizeof(*sect->neighbors));
				for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
                free(num);
                break;
            case 'p':; // player

                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player_init(pl, &v, &angle, &n); // TODO: Range checking
                pl->where.z = pl->sectors[pl->sector].floor + EYEHEIGHT;
        }
    fclose(fp);
    free(vert);
}
*/